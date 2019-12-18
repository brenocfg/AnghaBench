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
typedef  int register_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_MASK ; 
 int TLBHI_ASID_MASK ; 
 int TLBHI_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int) ; 
 int mips_rd_entryhi () ; 
 int /*<<< orphan*/  mips_wr_entryhi (int) ; 
 int /*<<< orphan*/  mips_wr_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_entrylo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_index (unsigned int) ; 
 int /*<<< orphan*/  mips_wr_pagemask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 

void
tlb_insert_wired(unsigned i, vm_offset_t va, pt_entry_t pte0, pt_entry_t pte1)
{
	register_t asid;
	register_t s;

	va &= ~PAGE_MASK;

	s = intr_disable();
	asid = mips_rd_entryhi() & TLBHI_ASID_MASK;

	mips_wr_index(i);
	mips_wr_pagemask(0);
	mips_wr_entryhi(TLBHI_ENTRY(va, 0));
	mips_wr_entrylo0(pte0);
	mips_wr_entrylo1(pte1);
	tlb_write_indexed();

	mips_wr_entryhi(asid);
	intr_restore(s);
}