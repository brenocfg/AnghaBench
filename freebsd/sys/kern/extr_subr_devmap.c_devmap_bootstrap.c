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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct devmap_entry {scalar_t__ pd_size; int /*<<< orphan*/  pd_pa; int /*<<< orphan*/  pd_va; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_DEVICE ; 
 int /*<<< orphan*/  VM_MEMATTR_DEVICE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int devmap_bootstrap_done ; 
 struct devmap_entry const* devmap_table ; 
 int /*<<< orphan*/  pmap_kenter_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_map_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_preboot_map_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

void
devmap_bootstrap(vm_offset_t l1pt, const struct devmap_entry *table)
{
	const struct devmap_entry *pd;

	devmap_bootstrap_done = true;

	/*
	 * If given a table pointer, use it.  Otherwise, if a table was
	 * previously registered, use it.  Otherwise, no work to do.
	 */
	if (table != NULL)
		devmap_table = table;
	else if (devmap_table == NULL)
		return;

	for (pd = devmap_table; pd->pd_size != 0; ++pd) {
#if defined(__arm__)
#if __ARM_ARCH >= 6
		pmap_preboot_map_attr(pd->pd_pa, pd->pd_va, pd->pd_size,
		    VM_PROT_READ | VM_PROT_WRITE, VM_MEMATTR_DEVICE);
#else
		pmap_map_chunk(l1pt, pd->pd_va, pd->pd_pa, pd->pd_size,
		    VM_PROT_READ | VM_PROT_WRITE, PTE_DEVICE);
#endif
#elif defined(__aarch64__) || defined(__riscv)
		pmap_kenter_device(pd->pd_va, pd->pd_size, pd->pd_pa);
#endif
	}
}