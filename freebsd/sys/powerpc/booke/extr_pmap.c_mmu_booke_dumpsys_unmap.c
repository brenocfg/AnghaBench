#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_size_t ;
typedef  size_t vm_paddr_t ;
typedef  size_t vm_offset_t ;
struct TYPE_4__ {int mas1; scalar_t__ mas3; scalar_t__ mas2; } ;
typedef  TYPE_1__ tlb_entry_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int MAS1_VALID ; 
 int TLB1_ENTRIES ; 
 scalar_t__ do_minidump ; 
 size_t rounddown2 (size_t,size_t) ; 
 int /*<<< orphan*/  tlb1_read_entry (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tlb1_write_entry (TYPE_1__*,int) ; 

void
mmu_booke_dumpsys_unmap(mmu_t mmu, vm_paddr_t pa, size_t sz, void *va)
{
	vm_paddr_t ppa;
	vm_offset_t ofs;
	vm_size_t gran;
	tlb_entry_t e;
	int i;

	/* Minidumps are based on virtual memory addresses. */
	/* Nothing to do... */
	if (do_minidump)
		return;

	for (i = 0; i < TLB1_ENTRIES; i++) {
		tlb1_read_entry(&e, i);
		if (!(e.mas1 & MAS1_VALID))
			break;
	}

	/* Raw physical memory dumps don't have a virtual address. */
	i--;
	e.mas1 = 0;
	e.mas2 = 0;
	e.mas3 = 0;
	tlb1_write_entry(&e, i);

	gran = 256 * 1024 * 1024;
	ppa = rounddown2(pa, gran);
	ofs = pa - ppa;
	if (sz > (gran - ofs)) {
		i--;
		e.mas1 = 0;
		e.mas2 = 0;
		e.mas3 = 0;
		tlb1_write_entry(&e, i);
	}
}