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
struct eeh_dev {TYPE_1__* pdev; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; scalar_t__ msix_enabled; scalar_t__ msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_DEV_IRQ_DISABLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_has_action (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eeh_disable_irq(struct eeh_dev *edev)
{
	/* Don't disable MSI and MSI-X interrupts. They are
	 * effectively disabled by the DMA Stopped state
	 * when an EEH error occurs.
	 */
	if (edev->pdev->msi_enabled || edev->pdev->msix_enabled)
		return;

	if (!irq_has_action(edev->pdev->irq))
		return;

	edev->mode |= EEH_DEV_IRQ_DISABLED;
	disable_irq_nosync(edev->pdev->irq);
}