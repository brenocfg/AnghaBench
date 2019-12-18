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
struct driver_data {scalar_t__ mmio; int /*<<< orphan*/  port; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ HOST_CTL ; 
 int HOST_IRQ_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hba_setup (struct driver_data*) ; 
 scalar_t__ mtip_hba_reset (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_init_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_start_port (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_hw_resume(struct driver_data *dd)
{
	/* Perform any needed hardware setup steps */
	hba_setup(dd);

	/* Reset the HBA */
	if (mtip_hba_reset(dd) != 0) {
		dev_err(&dd->pdev->dev,
			"Unable to reset the HBA\n");
		return -EFAULT;
	}

	/*
	 * Enable the port, DMA engine, and FIS reception specific
	 * h/w in controller.
	 */
	mtip_init_port(dd->port);
	mtip_start_port(dd->port);

	/* Enable interrupts on the HBA.*/
	writel(readl(dd->mmio + HOST_CTL) | HOST_IRQ_EN,
			dd->mmio + HOST_CTL);

	return 0;
}