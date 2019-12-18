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

/* Variables and functions */
 scalar_t__ MIPS_KSEG0_START ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TLBHI_ENTRY (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_entryhi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_entrylo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_index (unsigned int) ; 
 int /*<<< orphan*/  mips_wr_pagemask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 

__attribute__((used)) static void
tlb_invalidate_one(unsigned i)
{
	/* XXX an invalid ASID? */
	mips_wr_entryhi(TLBHI_ENTRY(MIPS_KSEG0_START + (2 * i * PAGE_SIZE), 0));
	mips_wr_entrylo0(0);
	mips_wr_entrylo1(0);
	mips_wr_pagemask(0);
	mips_wr_index(i);
	tlb_write_indexed();
}