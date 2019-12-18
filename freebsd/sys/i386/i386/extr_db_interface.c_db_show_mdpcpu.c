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
typedef  int /*<<< orphan*/  u_int ;
struct pcpu {int /*<<< orphan*/  pc_smp_tlb_done; scalar_t__ pc_common_tssp; int /*<<< orphan*/  pc_kesp0; int /*<<< orphan*/  pc_trampstk; int /*<<< orphan*/  pc_currentldt; int /*<<< orphan*/  pc_apic_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ) ; 

void
db_show_mdpcpu(struct pcpu *pc)
{

	db_printf("APIC ID      = %d\n", pc->pc_apic_id);
	db_printf("currentldt   = 0x%x\n", pc->pc_currentldt);
	db_printf("trampstk     = 0x%x\n", pc->pc_trampstk);
	db_printf("kesp0        = 0x%x\n", pc->pc_kesp0);
	db_printf("common_tssp  = 0x%x\n", (u_int)pc->pc_common_tssp);
	db_printf("tlb gen      = %u\n", pc->pc_smp_tlb_done);
}