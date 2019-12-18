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
typedef  size_t vm_size_t ;
typedef  size_t vm_paddr_t ;
typedef  size_t vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  _TLB_ENTRY_IO ; 
 scalar_t__ do_minidump ; 
 size_t rounddown2 (size_t,size_t) ; 
 int /*<<< orphan*/  tlb1_set_entry (size_t,size_t,size_t,int /*<<< orphan*/ ) ; 

void
mmu_booke_dumpsys_map(mmu_t mmu, vm_paddr_t pa, size_t sz, void **va)
{
	vm_paddr_t ppa;
	vm_offset_t ofs;
	vm_size_t gran;

	/* Minidumps are based on virtual memory addresses. */
	if (do_minidump) {
		*va = (void *)(vm_offset_t)pa;
		return;
	}

	/* Raw physical memory dumps don't have a virtual address. */
	/* We always map a 256MB page at 256M. */
	gran = 256 * 1024 * 1024;
	ppa = rounddown2(pa, gran);
	ofs = pa - ppa;
	*va = (void *)gran;
	tlb1_set_entry((vm_offset_t)va, ppa, gran, _TLB_ENTRY_IO);

	if (sz > (gran - ofs))
		tlb1_set_entry((vm_offset_t)(va + gran), ppa + gran, gran,
		    _TLB_ENTRY_IO);
}