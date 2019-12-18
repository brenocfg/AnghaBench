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

void ct_compute_clock (long hz, long baud, int *txbr, int *tmc)
{
	if (baud < 100)
		baud = 100;
	*txbr = 0;
	if (4*baud > 3*hz)
		*tmc = 1;
	else {
		while (((hz / baud) >> ++*txbr) > 256)
			continue;
		*tmc = (((2 * hz / baud) >> *txbr) + 1) / 2;
	}
}