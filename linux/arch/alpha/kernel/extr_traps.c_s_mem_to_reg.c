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

__attribute__((used)) static inline unsigned long
s_mem_to_reg (unsigned long s_mem)
{
	unsigned long frac    = (s_mem >>  0) & 0x7fffff;
	unsigned long sign    = (s_mem >> 31) & 0x1;
	unsigned long exp_msb = (s_mem >> 30) & 0x1;
	unsigned long exp_low = (s_mem >> 23) & 0x7f;
	unsigned long exp;

	exp = (exp_msb << 10) | exp_low;	/* common case */
	if (exp_msb) {
		if (exp_low == 0x7f) {
			exp = 0x7ff;
		}
	} else {
		if (exp_low == 0x00) {
			exp = 0x000;
		} else {
			exp |= (0x7 << 7);
		}
	}
	return (sign << 63) | (exp << 52) | (frac << 29);
}