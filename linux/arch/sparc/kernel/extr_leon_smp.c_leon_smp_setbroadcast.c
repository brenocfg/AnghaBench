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
struct TYPE_2__ {int /*<<< orphan*/  mpbroadcast; int /*<<< orphan*/  mpstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int LEON3_BYPASS_LOAD_PA (int /*<<< orphan*/ *) ; 
 int LEON3_IRQMPSTATUS_BROADCAST ; 
 int /*<<< orphan*/  LEON_BYPASS_STORE_PA (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__* leon3_irqctrl_regs ; 
 int leon_smp_nrcpus () ; 
 int /*<<< orphan*/  prom_printf (char*,...) ; 

__attribute__((used)) static void leon_smp_setbroadcast(unsigned int mask)
{
	int broadcast =
	    ((LEON3_BYPASS_LOAD_PA(&(leon3_irqctrl_regs->mpstatus)) >>
	      LEON3_IRQMPSTATUS_BROADCAST) & 1);
	if (!broadcast) {
		prom_printf("######## !!!! The irqmp-ctrl must have broadcast enabled, smp wont work !!!!! ####### nr cpus: %d\n",
		     leon_smp_nrcpus());
		if (leon_smp_nrcpus() > 1) {
			BUG();
		} else {
			prom_printf("continue anyway\n");
			return;
		}
	}
	LEON_BYPASS_STORE_PA(&(leon3_irqctrl_regs->mpbroadcast), mask);
}