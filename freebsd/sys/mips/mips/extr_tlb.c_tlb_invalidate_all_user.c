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
struct pmap {int dummy; } ;
typedef  int register_t ;

/* Variables and functions */
 int TLBHI_ASID_MASK ; 
 int intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int) ; 
 int mips_rd_entryhi () ; 
 unsigned int mips_rd_wired () ; 
 int /*<<< orphan*/  mips_wr_entryhi (int) ; 
 int /*<<< orphan*/  mips_wr_index (unsigned int) ; 
 unsigned int num_tlbentries ; 
 int pmap_asid (struct pmap*) ; 
 int /*<<< orphan*/  tlb_invalidate_one (unsigned int) ; 
 int /*<<< orphan*/  tlb_read () ; 

void
tlb_invalidate_all_user(struct pmap *pmap)
{
	register_t asid;
	register_t s;
	unsigned i;

	s = intr_disable();
	asid = mips_rd_entryhi() & TLBHI_ASID_MASK;

	for (i = mips_rd_wired(); i < num_tlbentries; i++) {
		register_t uasid;

		mips_wr_index(i);
		tlb_read();

		uasid = mips_rd_entryhi() & TLBHI_ASID_MASK;
		if (pmap == NULL) {
			/*
			 * Invalidate all non-kernel entries.
			 */
			if (uasid == 0)
				continue;
		} else {
			/*
			 * Invalidate this pmap's entries.
			 */
			if (uasid != pmap_asid(pmap))
				continue;
		}
		tlb_invalidate_one(i);
	}

	mips_wr_entryhi(asid);
	intr_restore(s);
}