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
struct pcpu {int /*<<< orphan*/  pc_smp_tlb_done; int /*<<< orphan*/  pc_tss; int /*<<< orphan*/  pc_ldt; int /*<<< orphan*/  pc_gs32p; int /*<<< orphan*/  pc_saved_ucr3; int /*<<< orphan*/  pc_ucr3; int /*<<< orphan*/  pc_kcr3; int /*<<< orphan*/  pc_rsp0; int /*<<< orphan*/  pc_tssp; int /*<<< orphan*/  pc_curpmap; int /*<<< orphan*/  pc_prvspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ) ; 

void
db_show_mdpcpu(struct pcpu *pc)
{

	db_printf("self         = %p\n", pc->pc_prvspace);
	db_printf("curpmap      = %p\n", pc->pc_curpmap);
	db_printf("tssp         = %p\n", pc->pc_tssp);
	db_printf("rsp0         = 0x%lx\n", pc->pc_rsp0);
	db_printf("kcr3         = 0x%lx\n", pc->pc_kcr3);
	db_printf("ucr3         = 0x%lx\n", pc->pc_ucr3);
	db_printf("scr3         = 0x%lx\n", pc->pc_saved_ucr3);
	db_printf("gs32p        = %p\n", pc->pc_gs32p);
	db_printf("ldt          = %p\n", pc->pc_ldt);
	db_printf("tss          = %p\n", pc->pc_tss);
	db_printf("tlb gen      = %u\n", pc->pc_smp_tlb_done);
}