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
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift (int,int,int /*<<< orphan*/ ) ; 

void cvmx_helper_qlm_jtag_shift_zeros(int qlm, int bits)
{
	while (bits > 0) {
		int n = bits;
		if (n > 32)
			n = 32;
		cvmx_helper_qlm_jtag_shift(qlm, n, 0);
		bits -= n;
	}
}