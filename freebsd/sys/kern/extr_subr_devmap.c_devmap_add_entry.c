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
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
struct devmap_entry {int pd_pa; int pd_size; scalar_t__ pd_va; } ;

/* Variables and functions */
 int AKVA_DEVMAP_MAX_ENTRIES ; 
 struct devmap_entry* akva_devmap_entries ; 
 int akva_devmap_idx ; 
 scalar_t__ akva_devmap_vaddr ; 
 scalar_t__ devmap_bootstrap_done ; 
 int /*<<< orphan*/  devmap_register_table (struct devmap_entry*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ trunc_1mpage (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

void
devmap_add_entry(vm_paddr_t pa, vm_size_t sz)
{
	struct devmap_entry *m;

	if (devmap_bootstrap_done)
		panic("devmap_add_entry() after devmap_bootstrap()");

	if (akva_devmap_idx == (AKVA_DEVMAP_MAX_ENTRIES - 1))
		panic("AKVA_DEVMAP_MAX_ENTRIES is too small");

	if (akva_devmap_idx == 0)
		devmap_register_table(akva_devmap_entries);

	 /* Allocate virtual address space from the top of kva downwards. */
#ifdef __arm__
	/*
	 * If the range being mapped is aligned and sized to 1MB boundaries then
	 * also align the virtual address to the next-lower 1MB boundary so that
	 * we end with a nice efficient section mapping.
	 */
	if ((pa & 0x000fffff) == 0 && (sz & 0x000fffff) == 0) {
		akva_devmap_vaddr = trunc_1mpage(akva_devmap_vaddr - sz);
	} else
#endif
	{
		akva_devmap_vaddr = trunc_page(akva_devmap_vaddr - sz);
	}
	m = &akva_devmap_entries[akva_devmap_idx++];
	m->pd_va    = akva_devmap_vaddr;
	m->pd_pa    = pa;
	m->pd_size  = sz;
}