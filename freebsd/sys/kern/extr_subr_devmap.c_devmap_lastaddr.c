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
typedef  scalar_t__ vm_offset_t ;
struct devmap_entry {scalar_t__ pd_size; scalar_t__ pd_va; } ;

/* Variables and functions */
 scalar_t__ DEVMAP_MAX_VADDR ; 
 scalar_t__ akva_devmap_idx ; 
 scalar_t__ akva_devmap_vaddr ; 
 struct devmap_entry* devmap_table ; 

vm_offset_t
devmap_lastaddr()
{
	const struct devmap_entry *pd;
	vm_offset_t lowaddr;

	if (akva_devmap_idx > 0)
		return (akva_devmap_vaddr);

	lowaddr = DEVMAP_MAX_VADDR;
	for (pd = devmap_table; pd != NULL && pd->pd_size != 0; ++pd) {
		if (lowaddr > pd->pd_va)
			lowaddr = pd->pd_va;
	}

	return (lowaddr);
}