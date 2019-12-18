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
typedef  TYPE_1__* devclass_t ;
struct TYPE_3__ {int maxunit; scalar_t__* devices; } ;

/* Variables and functions */

int
devclass_get_count(devclass_t dc)
{
	int count, i;

	count = 0;
	for (i = 0; i < dc->maxunit; i++)
		if (dc->devices[i])
			count++;
	return (count);
}