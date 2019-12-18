#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int uint32_t ;
typedef  int uint16_t ;
typedef  int int32_t ;

/* Variables and functions */
 unsigned int int32_sflag (int) ; 
 unsigned int int32_to_uint32_2cpl (int) ; 
 int uint32_2cpl_to_int32 (unsigned int) ; 

int32_t
isocal_weeks_in_years(
	int32_t years
	)
{	
	/*
	 * use: w = (y * 53431 + b[c]) / 1024 as interpolation
	 */
	static const uint16_t bctab[4] = { 157, 449, 597, 889 };

	int32_t  cs, cw;
	uint32_t cc, ci, yu, sflag;

	sflag = int32_sflag(years);
	yu    = int32_to_uint32_2cpl(years);
	
	/* split off centuries, using floor division */
	cc  = sflag ^ ((sflag ^ yu) / 100u);
	yu -= cc * 100u;

	/* calculate century cycles shift and cycle index:
	 * Assuming a century is 5217 weeks, we have to add a cycle
	 * shift that is 3 for every 4 centuries, because 3 of the four
	 * centuries have 5218 weeks. So '(cc*3 + 1) / 4' is the actual
	 * correction, and the second century is the defective one.
	 *
	 * Needs floor division by 4, which is done with masking and
	 * shifting.
	 */
	ci = cc * 3u + 1;
	cs = uint32_2cpl_to_int32(sflag ^ ((sflag ^ ci) / 4u));
	ci = ci % 4u;
	
	/* Get weeks in century. Can use plain division here as all ops
	 * are >= 0,  and let the compiler sort out the possible
	 * optimisations.
	 */
	cw = (yu * 53431u + bctab[ci]) / 1024u;

	return uint32_2cpl_to_int32(cc) * 5217 + cs + cw;
}