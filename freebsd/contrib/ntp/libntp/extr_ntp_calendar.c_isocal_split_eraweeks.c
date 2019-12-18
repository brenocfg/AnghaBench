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
typedef  int uint16_t ;
struct TYPE_3__ {int hi; unsigned int lo; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  size_t int32_t ;

/* Variables and functions */
 unsigned int GREGORIAN_CYCLE_WEEKS ; 
 unsigned int int32_sflag (size_t) ; 
 int /*<<< orphan*/  int32_to_uint32_2cpl (size_t) ; 
 size_t uint32_2cpl_to_int32 (unsigned int) ; 
 unsigned int uint32_saturate (int /*<<< orphan*/ ,unsigned int) ; 

ntpcal_split
isocal_split_eraweeks(
	int32_t weeks
	)
{
	/*
	 * use: y = (w * 157 + b[c]) / 8192 as interpolation
	 */

	static const uint16_t bctab[4] = { 85, 130, 17, 62 };

	ntpcal_split res;
	int32_t  cc, ci;
	uint32_t sw, cy, Q, sflag;

	/* Use two fast cycle-split divisions here. This is again
	 * susceptible to internal overflow, so we check the range. This
	 * still permits more than +/-20 million years, so this is
	 * likely a pure academical problem.
	 *
	 * We want to execute '(weeks * 4 + 2) /% 20871' under floor
	 * division rules in the first step.
	 */
	sflag = int32_sflag(weeks);
	sw  = uint32_saturate(int32_to_uint32_2cpl(weeks), sflag);
	sw  = 4u * sw + 2;
	Q   = sflag ^ ((sflag ^ sw) / GREGORIAN_CYCLE_WEEKS);
	sw -= Q * GREGORIAN_CYCLE_WEEKS;
	ci  = Q % 4u;
	cc  = uint32_2cpl_to_int32(Q);

	/* Split off years; sw >= 0 here! The scaled weeks in the years
	 * are scaled up by 157 afterwards.
	 */ 
	sw  = (sw / 4u) * 157u + bctab[ci];
	cy  = sw / 8192u;	/* ws >> 13 , let the compiler sort it out */
	sw  = sw % 8192u;	/* ws & 8191, let the compiler sort it out */

	/* assemble elapsed years and downscale the elapsed weeks in
	 * the year.
	 */
	res.hi = 100*cc + cy;
	res.lo = sw / 157u;

	return res;
}