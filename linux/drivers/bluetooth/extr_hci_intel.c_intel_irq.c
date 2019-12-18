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
struct intel_device {TYPE_1__* pdev; int /*<<< orphan*/  hu_lock; scalar_t__ hu; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  intel_lpm_host_wake (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t intel_irq(int irq, void *dev_id)
{
	struct intel_device *idev = dev_id;

	dev_info(&idev->pdev->dev, "hci_intel irq\n");

	mutex_lock(&idev->hu_lock);
	if (idev->hu)
		intel_lpm_host_wake(idev->hu);
	mutex_unlock(&idev->hu_lock);

	/* Host/Controller are now LPM resumed, trigger a new delayed suspend */
	pm_runtime_get(&idev->pdev->dev);
	pm_runtime_mark_last_busy(&idev->pdev->dev);
	pm_runtime_put_autosuspend(&idev->pdev->dev);

	return IRQ_HANDLED;
}