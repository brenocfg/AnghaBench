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
struct wake_irq {int status; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WAKE_IRQ_DEDICATED_ALLOCATED ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ ) ; 

void dev_pm_disarm_wake_irq(struct wake_irq *wirq)
{
	if (!wirq)
		return;

	if (device_may_wakeup(wirq->dev)) {
		disable_irq_wake(wirq->irq);

		if (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED &&
		    !pm_runtime_status_suspended(wirq->dev))
			disable_irq_nosync(wirq->irq);
	}
}