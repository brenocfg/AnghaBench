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
typedef  scalar_t__ vm_paddr_t ;

/* Variables and functions */
 scalar_t__* physmem_desc ; 

int
is_cacheable_mem(vm_paddr_t pa)
{
	int i;

	for (i = 0; physmem_desc[i + 1] != 0; i += 2) {
		if (pa >= physmem_desc[i] && pa < physmem_desc[i + 1])
			return (1);
	}

	return (0);
}