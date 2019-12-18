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
struct proc_ldt {int /*<<< orphan*/  ldt_sd; } ;
struct mdproc {struct proc_ldt* md_ldt; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSEL (int,int /*<<< orphan*/ ) ; 
 int GUSERLDT_SEL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int NGDT ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  currentldt ; 
 int /*<<< orphan*/  dt_lock ; 
 TYPE_1__* gdt ; 
 int /*<<< orphan*/  lldt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_user_ldt_locked(struct mdproc *mdp)
{
	struct proc_ldt *pldt;
	int gdt_idx;

	mtx_assert(&dt_lock, MA_OWNED);

	pldt = mdp->md_ldt;
	gdt_idx = GUSERLDT_SEL;
	gdt_idx += PCPU_GET(cpuid) * NGDT;	/* always 0 on UP */
	gdt[gdt_idx].sd = pldt->ldt_sd;
	lldt(GSEL(GUSERLDT_SEL, SEL_KPL));
	PCPU_SET(currentldt, GSEL(GUSERLDT_SEL, SEL_KPL));
}