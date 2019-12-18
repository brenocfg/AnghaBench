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

/* Variables and functions */
 unsigned int VSCR_SAT ; 

__attribute__((used)) static unsigned int ctuxs(unsigned int x, int scale, unsigned int *vscrp)
{
	int exp;
	unsigned int mant;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	if (exp == 255 && mant != 0)
		return 0;		/* NaN -> 0 */
	exp = exp - 127 + scale;
	if (exp < 0)
		return 0;		/* round towards zero */
	if (x & 0x80000000) {
		/* negative => saturate to 0 */
		*vscrp |= VSCR_SAT;
		return 0;
	}
	if (exp >= 32) {
		/* saturate */
		*vscrp |= VSCR_SAT;
		return 0xffffffff;
	}
	mant |= 0x800000;
	mant = (mant << 8) >> (31 - exp);
	return mant;
}