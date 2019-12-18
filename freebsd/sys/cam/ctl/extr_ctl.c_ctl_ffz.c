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
typedef  int uint32_t ;

/* Variables and functions */

int
ctl_ffz(uint32_t *mask, uint32_t first, uint32_t last)
{
	int i;

	for (i = first; i < last; i++) {
		if ((mask[i / 32] & (1 << (i % 32))) == 0)
			return (i);
	}
	return (-1);
}