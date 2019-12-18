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
typedef  int register_t ;

/* Variables and functions */
 int TLBHI_ASID_MASK ; 
 int intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int) ; 
 int mips_rd_entryhi () ; 
 unsigned int mips_rd_wired () ; 
 int /*<<< orphan*/  mips_wr_entryhi (int) ; 
 unsigned int num_tlbentries ; 
 int /*<<< orphan*/  tlb_invalidate_one (unsigned int) ; 

void
tlb_invalidate_all(void)
{
	register_t asid;
	register_t s;
	unsigned i;

	s = intr_disable();
	asid = mips_rd_entryhi() & TLBHI_ASID_MASK;

	for (i = mips_rd_wired(); i < num_tlbentries; i++)
		tlb_invalidate_one(i);

	mips_wr_entryhi(asid);
	intr_restore(s);
}