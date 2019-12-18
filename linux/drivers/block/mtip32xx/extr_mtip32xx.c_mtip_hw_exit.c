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
struct driver_data {int /*<<< orphan*/ * port; TYPE_1__* pdev; scalar_t__ mmio; int /*<<< orphan*/  sr; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ HOST_CTL ; 
 int HOST_IRQ_EN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct driver_data*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtip_deinit_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtip_dma_free (struct driver_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_hw_exit(struct driver_data *dd)
{
	if (!dd->sr) {
		/* de-initialize the port. */
		mtip_deinit_port(dd->port);

		/* Disable interrupts on the HBA. */
		writel(readl(dd->mmio + HOST_CTL) & ~HOST_IRQ_EN,
				dd->mmio + HOST_CTL);
	}

	/* Release the IRQ. */
	irq_set_affinity_hint(dd->pdev->irq, NULL);
	free_irq(dd->pdev->irq, dd);
	msleep(1000);

	/* Free dma regions */
	mtip_dma_free(dd);

	/* Free the memory allocated for the for structure. */
	kfree(dd->port);
	dd->port = NULL;

	return 0;
}