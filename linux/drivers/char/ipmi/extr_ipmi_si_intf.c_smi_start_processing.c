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
struct TYPE_2__ {scalar_t__ si_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  (* irq_setup ) (TYPE_1__*) ;struct smi_info* irq_handler_data; } ;
struct smi_info {int timer_can_start; size_t si_num; int /*<<< orphan*/ * thread; TYPE_1__ io; int /*<<< orphan*/  si_timer; struct ipmi_smi* intf; } ;
struct ipmi_smi {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SI_BT ; 
 scalar_t__ SI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int* force_kipmid ; 
 int /*<<< orphan*/  ipmi_thread ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct smi_info*,char*,size_t) ; 
 size_t num_force_kipmid ; 
 int /*<<< orphan*/  smi_mod_timer (struct smi_info*,scalar_t__) ; 
 int /*<<< orphan*/  smi_timeout ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smi_start_processing(void            *send_info,
				struct ipmi_smi *intf)
{
	struct smi_info *new_smi = send_info;
	int             enable = 0;

	new_smi->intf = intf;

	/* Set up the timer that drives the interface. */
	timer_setup(&new_smi->si_timer, smi_timeout, 0);
	new_smi->timer_can_start = true;
	smi_mod_timer(new_smi, jiffies + SI_TIMEOUT_JIFFIES);

	/* Try to claim any interrupts. */
	if (new_smi->io.irq_setup) {
		new_smi->io.irq_handler_data = new_smi;
		new_smi->io.irq_setup(&new_smi->io);
	}

	/*
	 * Check if the user forcefully enabled the daemon.
	 */
	if (new_smi->si_num < num_force_kipmid)
		enable = force_kipmid[new_smi->si_num];
	/*
	 * The BT interface is efficient enough to not need a thread,
	 * and there is no need for a thread if we have interrupts.
	 */
	else if ((new_smi->io.si_type != SI_BT) && (!new_smi->io.irq))
		enable = 1;

	if (enable) {
		new_smi->thread = kthread_run(ipmi_thread, new_smi,
					      "kipmi%d", new_smi->si_num);
		if (IS_ERR(new_smi->thread)) {
			dev_notice(new_smi->io.dev, "Could not start"
				   " kernel thread due to error %ld, only using"
				   " timers to drive the interface\n",
				   PTR_ERR(new_smi->thread));
			new_smi->thread = NULL;
		}
	}

	return 0;
}