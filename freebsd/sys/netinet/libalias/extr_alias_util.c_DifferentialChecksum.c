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
typedef  int u_short ;

/* Variables and functions */

void
DifferentialChecksum(u_short * cksum, void *newp, void *oldp, int n)
{
	int i;
	int accumulate;
	u_short *new = newp;
	u_short *old = oldp;

	accumulate = *cksum;
	for (i = 0; i < n; i++) {
		accumulate -= *new++;
		accumulate += *old++;
	}

	if (accumulate < 0) {
		accumulate = -accumulate;
		accumulate = (accumulate >> 16) + (accumulate & 0xffff);
		accumulate += accumulate >> 16;
		*cksum = (u_short) ~ accumulate;
	} else {
		accumulate = (accumulate >> 16) + (accumulate & 0xffff);
		accumulate += accumulate >> 16;
		*cksum = (u_short) accumulate;
	}
}