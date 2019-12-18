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
struct wake_irq {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 scalar_t__ irqd_is_wakeup_set (int /*<<< orphan*/ ) ; 
 int pm_runtime_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t handle_threaded_wake_irq(int irq, void *_wirq)
{
	struct wake_irq *wirq = _wirq;
	int res;

	/* Maybe abort suspend? */
	if (irqd_is_wakeup_set(irq_get_irq_data(irq))) {
		pm_wakeup_event(wirq->dev, 0);

		return IRQ_HANDLED;
	}

	/* We don't want RPM_ASYNC or RPM_NOWAIT here */
	res = pm_runtime_resume(wirq->dev);
	if (res < 0)
		dev_warn(wirq->dev,
			 "wake IRQ with no resume: %i\n", res);

	return IRQ_HANDLED;
}