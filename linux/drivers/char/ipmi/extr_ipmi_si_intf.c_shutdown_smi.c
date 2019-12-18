#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* io_cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  (* addr_source_cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  (* irq_cleanup ) (TYPE_2__*) ;scalar_t__ dev; } ;
struct smi_info {int dev_group_added; int interrupt_disabled; scalar_t__ si_state; int /*<<< orphan*/ * intf; int /*<<< orphan*/ * si_sm; TYPE_2__ io; TYPE_1__* handlers; scalar_t__ curr_msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ SI_NORMAL ; 
 int /*<<< orphan*/  dev_set_drvdata (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_group (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_si_irq (struct smi_info*) ; 
 int /*<<< orphan*/  ipmi_si_dev_attr_group ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll (struct smi_info*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  stop_timer_and_thread (struct smi_info*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void shutdown_smi(void *send_info)
{
	struct smi_info *smi_info = send_info;

	if (smi_info->dev_group_added) {
		device_remove_group(smi_info->io.dev, &ipmi_si_dev_attr_group);
		smi_info->dev_group_added = false;
	}
	if (smi_info->io.dev)
		dev_set_drvdata(smi_info->io.dev, NULL);

	/*
	 * Make sure that interrupts, the timer and the thread are
	 * stopped and will not run again.
	 */
	smi_info->interrupt_disabled = true;
	if (smi_info->io.irq_cleanup) {
		smi_info->io.irq_cleanup(&smi_info->io);
		smi_info->io.irq_cleanup = NULL;
	}
	stop_timer_and_thread(smi_info);

	/*
	 * Wait until we know that we are out of any interrupt
	 * handlers might have been running before we freed the
	 * interrupt.
	 */
	synchronize_rcu();

	/*
	 * Timeouts are stopped, now make sure the interrupts are off
	 * in the BMC.  Note that timers and CPU interrupts are off,
	 * so no need for locks.
	 */
	while (smi_info->curr_msg || (smi_info->si_state != SI_NORMAL)) {
		poll(smi_info);
		schedule_timeout_uninterruptible(1);
	}
	if (smi_info->handlers)
		disable_si_irq(smi_info);
	while (smi_info->curr_msg || (smi_info->si_state != SI_NORMAL)) {
		poll(smi_info);
		schedule_timeout_uninterruptible(1);
	}
	if (smi_info->handlers)
		smi_info->handlers->cleanup(smi_info->si_sm);

	if (smi_info->io.addr_source_cleanup) {
		smi_info->io.addr_source_cleanup(&smi_info->io);
		smi_info->io.addr_source_cleanup = NULL;
	}
	if (smi_info->io.io_cleanup) {
		smi_info->io.io_cleanup(&smi_info->io);
		smi_info->io.io_cleanup = NULL;
	}

	kfree(smi_info->si_sm);
	smi_info->si_sm = NULL;

	smi_info->intf = NULL;
}