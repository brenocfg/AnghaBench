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
struct ia64_mca_notify_die {int* monarch_cpu; int /*<<< orphan*/ * sos; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/ * imi_rendez_checkin; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_MCA_RENDZVOUS_ENTER ; 
 int /*<<< orphan*/  DIE_MCA_RENDZVOUS_LEAVE ; 
 int /*<<< orphan*/  DIE_MCA_RENDZVOUS_PROCESS ; 
 int /*<<< orphan*/  IA64_MCA_RENDEZ_CHECKIN_DONE ; 
 int /*<<< orphan*/  IA64_MCA_RENDEZ_CHECKIN_NOTDONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NOTIFY_MCA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 TYPE_1__ ia64_mc_info ; 
 int /*<<< orphan*/  ia64_sal_mc_rendez () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int monarch_cpu ; 
 int smp_processor_id () ; 

__attribute__((used)) static irqreturn_t
ia64_mca_rendez_int_handler(int rendez_irq, void *arg)
{
	unsigned long flags;
	int cpu = smp_processor_id();
	struct ia64_mca_notify_die nd =
		{ .sos = NULL, .monarch_cpu = &monarch_cpu };

	/* Mask all interrupts */
	local_irq_save(flags);

	NOTIFY_MCA(DIE_MCA_RENDZVOUS_ENTER, get_irq_regs(), (long)&nd, 1);

	ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_DONE;
	/* Register with the SAL monarch that the slave has
	 * reached SAL
	 */
	ia64_sal_mc_rendez();

	NOTIFY_MCA(DIE_MCA_RENDZVOUS_PROCESS, get_irq_regs(), (long)&nd, 1);

	/* Wait for the monarch cpu to exit. */
	while (monarch_cpu != -1)
	       cpu_relax();	/* spin until monarch leaves */

	NOTIFY_MCA(DIE_MCA_RENDZVOUS_LEAVE, get_irq_regs(), (long)&nd, 1);

	ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_NOTDONE;
	/* Enable all interrupts */
	local_irq_restore(flags);
	return IRQ_HANDLED;
}