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
struct pt_regs {int dummy; } ;
struct TYPE_4__ {scalar_t__ hmi_p9_special_emu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* handle_hmi_exception ) (struct pt_regs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 TYPE_2__* local_paca ; 
 int /*<<< orphan*/  p9_hmi_special_emu (struct pt_regs*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 TYPE_1__ ppc_md ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (struct pt_regs*) ; 

void handle_hmi_exception(struct pt_regs *regs)
{
	struct pt_regs *old_regs;

	old_regs = set_irq_regs(regs);
	irq_enter();

#ifdef CONFIG_VSX
	/* Real mode flagged P9 special emu is needed */
	if (local_paca->hmi_p9_special_emu) {
		local_paca->hmi_p9_special_emu = 0;

		/*
		 * We don't want to take page faults while doing the
		 * emulation, we just replay the instruction if necessary.
		 */
		pagefault_disable();
		p9_hmi_special_emu(regs);
		pagefault_enable();
	}
#endif /* CONFIG_VSX */

	if (ppc_md.handle_hmi_exception)
		ppc_md.handle_hmi_exception(regs);

	irq_exit();
	set_irq_regs(old_regs);
}