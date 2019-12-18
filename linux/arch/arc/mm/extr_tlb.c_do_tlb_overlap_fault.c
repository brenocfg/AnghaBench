#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct cpuinfo_arc_mmu {int ways; int sets; } ;
struct TYPE_2__ {struct cpuinfo_arc_mmu mmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_TLBCOMMAND ; 
 int /*<<< orphan*/  ARC_REG_TLBINDEX ; 
 int /*<<< orphan*/  ARC_REG_TLBPD0 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PAGE_MASK ; 
 int /*<<< orphan*/  SET_WAY_TO_IDX (struct cpuinfo_arc_mmu*,int,int) ; 
 int /*<<< orphan*/  TLBRead ; 
 unsigned int _PAGE_PRESENT ; 
 int /*<<< orphan*/  __tlb_entry_erase () ; 
 TYPE_1__* cpuinfo_arc700 ; 
 int /*<<< orphan*/  dup_pd_silent ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int,int,int) ; 
 unsigned int read_aux_reg (int /*<<< orphan*/ ) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_tlb_overlap_fault(unsigned long cause, unsigned long address,
			  struct pt_regs *regs)
{
	struct cpuinfo_arc_mmu *mmu = &cpuinfo_arc700[smp_processor_id()].mmu;
	unsigned long flags;
	int set, n_ways = mmu->ways;

	n_ways = min(n_ways, 4);
	BUG_ON(mmu->ways > 4);

	local_irq_save(flags);

	/* loop thru all sets of TLB */
	for (set = 0; set < mmu->sets; set++) {

		int is_valid, way;
		unsigned int pd0[4];

		/* read out all the ways of current set */
		for (way = 0, is_valid = 0; way < n_ways; way++) {
			write_aux_reg(ARC_REG_TLBINDEX,
					  SET_WAY_TO_IDX(mmu, set, way));
			write_aux_reg(ARC_REG_TLBCOMMAND, TLBRead);
			pd0[way] = read_aux_reg(ARC_REG_TLBPD0);
			is_valid |= pd0[way] & _PAGE_PRESENT;
			pd0[way] &= PAGE_MASK;
		}

		/* If all the WAYS in SET are empty, skip to next SET */
		if (!is_valid)
			continue;

		/* Scan the set for duplicate ways: needs a nested loop */
		for (way = 0; way < n_ways - 1; way++) {

			int n;

			if (!pd0[way])
				continue;

			for (n = way + 1; n < n_ways; n++) {
				if (pd0[way] != pd0[n])
					continue;

				if (!dup_pd_silent)
					pr_info("Dup TLB PD0 %08x @ set %d ways %d,%d\n",
						pd0[way], set, way, n);

				/*
				 * clear entry @way and not @n.
				 * This is critical to our optimised loop
				 */
				pd0[way] = 0;
				write_aux_reg(ARC_REG_TLBINDEX,
						SET_WAY_TO_IDX(mmu, set, way));
				__tlb_entry_erase();
			}
		}
	}

	local_irq_restore(flags);
}