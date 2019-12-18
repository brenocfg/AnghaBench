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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
struct devmap_entry {scalar_t__ pd_size; scalar_t__ pd_pa; scalar_t__ pd_va; } ;

/* Variables and functions */
 struct devmap_entry* devmap_table ; 

void *
devmap_ptov(vm_paddr_t pa, vm_size_t size)
{
	const struct devmap_entry *pd;

	if (devmap_table == NULL)
		return (NULL);

	for (pd = devmap_table; pd->pd_size != 0; ++pd) {
		if (pa >= pd->pd_pa && pa + size <= pd->pd_pa + pd->pd_size)
			return ((void *)(pd->pd_va + (pa - pd->pd_pa)));
	}

	return (NULL);
}