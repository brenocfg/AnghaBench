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

void cx_clock (long hz, long ba, int *clk, int *div)
{
	static short clocktab[] = { 8, 32, 128, 512, 2048, 0 };

	for (*clk=0; clocktab[*clk]; ++*clk) {
		long c = ba * clocktab[*clk];
		if (hz <= c*256) {
			*div = (2 * hz + c) / (2 * c) - 1;
			return;
		}
	}
	/* Incorrect baud rate.  Return some meaningful values. */
	*clk = 0;
	*div = 255;
}