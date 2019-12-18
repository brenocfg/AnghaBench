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

/* Variables and functions */

__attribute__((used)) static void update_refstatus(int *ref_status, int nr, uint32_t *bitmap)
{
	unsigned int i;
	if (!ref_status)
		return;
	for (i = 0; i < nr; i++)
		if (bitmap[i / 32] & (1U << (i % 32)))
			ref_status[i]++;
}