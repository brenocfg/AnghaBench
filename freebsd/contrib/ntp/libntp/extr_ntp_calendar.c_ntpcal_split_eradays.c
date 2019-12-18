#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_3__ {int hi; unsigned int lo; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  int int32_t ;

/* Variables and functions */
 unsigned int GREGORIAN_CYCLE_DAYS ; 
 unsigned int GREGORIAN_NORMAL_LEAP_CYCLE_DAYS ; 
 unsigned int int32_sflag (int) ; 
 int /*<<< orphan*/  int32_to_uint32_2cpl (int) ; 
 int uint32_2cpl_to_int32 (unsigned int) ; 
 unsigned int uint32_saturate (int /*<<< orphan*/ ,unsigned int) ; 

ntpcal_split
ntpcal_split_eradays(
	int32_t days,
	int  *isleapyear
	)
{
	/* Use the fast cyclesplit algorithm here, to calculate the
	 * centuries and years in a century with one division each. This
	 * reduces the number of division operations to two, but is
	 * susceptible to internal range overflow. We make sure the
	 * input operands are in the safe range; this still gives us
	 * approx +/-2.9 million years.
	 */
	ntpcal_split res;
	int32_t	 n100, n001; /* calendar year cycles */
	uint32_t uday, Q, sflag;

	/* split off centuries first */
	sflag = int32_sflag(days);
	uday  = uint32_saturate(int32_to_uint32_2cpl(days), sflag);
	uday  = (4u * uday) | 3u;
	Q    = sflag ^ ((sflag ^ uday) / GREGORIAN_CYCLE_DAYS);
	uday = uday - Q * GREGORIAN_CYCLE_DAYS;
	n100 = uint32_2cpl_to_int32(Q);
	
	/* Split off years in century -- days >= 0 here, and we're far
	 * away from integer overflow trouble now. */
	uday |= 3;
	n001 = uday / GREGORIAN_NORMAL_LEAP_CYCLE_DAYS;
	uday = uday % GREGORIAN_NORMAL_LEAP_CYCLE_DAYS;

	/* Assemble the year and day in year */
	res.hi = n100 * 100 + n001;
	res.lo = uday / 4u;

	/* Eventually set the leap year flag. Note: 0 <= n001 <= 99 and
	 * Q is still the two's complement representation of the
	 * centuries: The modulo 4 ops can be done with masking here.
	 * We also shift the year and the century by one, so the tests
	 * can be done against zero instead of 3.
	 */
	if (isleapyear)
		*isleapyear = !((n001+1) & 3)
		    && ((n001 != 99) || !((Q+1) & 3));
	
	return res;
}