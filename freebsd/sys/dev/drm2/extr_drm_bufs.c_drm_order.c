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

int drm_order(unsigned long size)
{
	int order;
	unsigned long tmp;

	for (order = 0, tmp = size >> 1; tmp; tmp >>= 1, order++) ;

	if (size & (size - 1))
		++order;

	return order;
}