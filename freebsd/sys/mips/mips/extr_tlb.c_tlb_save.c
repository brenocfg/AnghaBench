#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* entry; int /*<<< orphan*/  wired; } ;
struct TYPE_3__ {int /*<<< orphan*/  entrylo1; int /*<<< orphan*/  entrylo0; int /*<<< orphan*/  pagemask; int /*<<< orphan*/  entryhi; } ;

/* Variables and functions */
 unsigned int MIPS_MAX_TLB_ENTRIES ; 
 unsigned int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  mips_rd_entryhi () ; 
 int /*<<< orphan*/  mips_rd_entrylo0 () ; 
 int /*<<< orphan*/  mips_rd_entrylo1 () ; 
 int /*<<< orphan*/  mips_rd_pagemask () ; 
 int /*<<< orphan*/  mips_rd_wired () ; 
 int /*<<< orphan*/  mips_wr_index (unsigned int) ; 
 unsigned int num_tlbentries ; 
 int /*<<< orphan*/  tlb_read () ; 
 TYPE_2__* tlb_state ; 

void
tlb_save(void)
{
	unsigned ntlb, i, cpu;

	cpu = PCPU_GET(cpuid);
	if (num_tlbentries > MIPS_MAX_TLB_ENTRIES)
		ntlb = MIPS_MAX_TLB_ENTRIES;
	else
		ntlb = num_tlbentries;
	tlb_state[cpu].wired = mips_rd_wired();
	for (i = 0; i < ntlb; i++) {
		mips_wr_index(i);
		tlb_read();

		tlb_state[cpu].entry[i].entryhi = mips_rd_entryhi();
		tlb_state[cpu].entry[i].pagemask = mips_rd_pagemask();
		tlb_state[cpu].entry[i].entrylo0 = mips_rd_entrylo0();
		tlb_state[cpu].entry[i].entrylo1 = mips_rd_entrylo1();
	}
}