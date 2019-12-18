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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L2_SIZE ; 
 int PAGE_MASK ; 
 int VM_MAX_KERNEL_ADDRESS ; 
 int akva_devmap_vaddr ; 
 void* devmap_ptov (int,int /*<<< orphan*/ ) ; 
 scalar_t__ early_boot ; 
 int kva_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_kenter_device (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 void* trunc_page (int) ; 

void *
pmap_mapdev(vm_offset_t pa, vm_size_t size)
{
	vm_offset_t va, offset;
	void * rva;

	/* First look in the static mapping table. */
	if ((rva = devmap_ptov(pa, size)) != NULL)
		return (rva);

	offset = pa & PAGE_MASK;
	pa = trunc_page(pa);
	size = round_page(size + offset);

#if defined(__aarch64__) || defined(__riscv)
	if (early_boot) {
		akva_devmap_vaddr = trunc_page(akva_devmap_vaddr - size);
		va = akva_devmap_vaddr;
		KASSERT(va >= VM_MAX_KERNEL_ADDRESS - L2_SIZE,
		    ("Too many early devmap mappings"));
	} else
#endif
		va = kva_alloc(size);
	if (!va)
		panic("pmap_mapdev: Couldn't alloc kernel virtual memory");

	pmap_kenter_device(va, size, pa);

	return ((void *)(va + offset));
}