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
struct wake_irq {int irq; struct wake_irq* name; int /*<<< orphan*/  status; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  IRQ_DISABLE_UNLAZY ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  WAKE_IRQ_DEDICATED_ALLOCATED ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int dev_pm_attach_wake_irq (struct device*,int,struct wake_irq*) ; 
 int /*<<< orphan*/  free_irq (int,struct wake_irq*) ; 
 int /*<<< orphan*/  handle_threaded_wake_irq ; 
 int /*<<< orphan*/  irq_set_status_flags (int,int /*<<< orphan*/ ) ; 
 struct wake_irq* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wake_irq*) ; 
 struct wake_irq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wake_irq*,struct wake_irq*) ; 

int dev_pm_set_dedicated_wake_irq(struct device *dev, int irq)
{
	struct wake_irq *wirq;
	int err;

	if (irq < 0)
		return -EINVAL;

	wirq = kzalloc(sizeof(*wirq), GFP_KERNEL);
	if (!wirq)
		return -ENOMEM;

	wirq->name = kasprintf(GFP_KERNEL, "%s:wakeup", dev_name(dev));
	if (!wirq->name) {
		err = -ENOMEM;
		goto err_free;
	}

	wirq->dev = dev;
	wirq->irq = irq;
	irq_set_status_flags(irq, IRQ_NOAUTOEN);

	/* Prevent deferred spurious wakeirqs with disable_irq_nosync() */
	irq_set_status_flags(irq, IRQ_DISABLE_UNLAZY);

	/*
	 * Consumer device may need to power up and restore state
	 * so we use a threaded irq.
	 */
	err = request_threaded_irq(irq, NULL, handle_threaded_wake_irq,
				   IRQF_ONESHOT, wirq->name, wirq);
	if (err)
		goto err_free_name;

	err = dev_pm_attach_wake_irq(dev, irq, wirq);
	if (err)
		goto err_free_irq;

	wirq->status = WAKE_IRQ_DEDICATED_ALLOCATED;

	return err;

err_free_irq:
	free_irq(irq, wirq);
err_free_name:
	kfree(wirq->name);
err_free:
	kfree(wirq);

	return err;
}