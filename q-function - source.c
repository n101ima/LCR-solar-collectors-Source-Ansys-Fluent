#include "udf.h"
#include "mem.h"

DEFINE_SOURCE(heat_flux_source1, c, t, dS, eqn)
{
	real angle;
	real x[ND_ND];
	real heat_flux;
	real source;

	C_CENTROID(x, c, t);
	angle = atan2(x[1], x[0]);

	if (angle >= 0 && angle < 68)
		heat_flux = -2.588e-7 * pow(angle, 5) + 4.175e-5 * pow(angle, 4) - 2.258e-3 * pow(angle, 3) + 0.04643 * pow(angle, 2) - 0.01496 * angle + 26.65;
	else if (angle >= 68 && angle < 114)
		heat_flux = 4.071e-4 * pow(angle, 3) - 0.1121 * pow(angle, 2) + 9.099 * angle - 181.1;
	else if (angle >= 114 && angle < 180)
		heat_flux = -2.175e-6 * pow(angle, 3) + 1.135e-3 * pow(angle, 2) - 0.1821 * angle + 9.668;
	else
		heat_flux = 0;

	source = (heat_flux/15.0) / C_VOLUME(c, t); // Divide by cell volume to get source term *488.72
	dS[eqn] = 0; // No linearization

	return source;
}