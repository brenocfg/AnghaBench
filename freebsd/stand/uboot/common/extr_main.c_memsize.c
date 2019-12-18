#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct sys_info {int mr_no; TYPE_1__* mr; } ;
struct TYPE_2__ {int flags; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t
memsize(struct sys_info *si, int flags)
{
	uint64_t size;
	int i;

	size = 0;
	for (i = 0; i < si->mr_no; i++)
		if (si->mr[i].flags == flags && si->mr[i].size)
			size += (si->mr[i].size);

	return (size);
}