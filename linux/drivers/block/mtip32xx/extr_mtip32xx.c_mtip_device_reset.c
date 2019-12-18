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
struct driver_data {scalar_t__ mmio; int /*<<< orphan*/  port; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ HOST_CTL ; 
 int HOST_IRQ_EN ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ mtip_check_surprise_removal (int /*<<< orphan*/ ) ; 
 scalar_t__ mtip_hba_reset (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_init_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_start_port (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_device_reset(struct driver_data *dd)
{
	int rv = 0;

	if (mtip_check_surprise_removal(dd->pdev))
		return 0;

	if (mtip_hba_reset(dd) < 0)
		rv = -EFAULT;

	mdelay(1);
	mtip_init_port(dd->port);
	mtip_start_port(dd->port);

	/* Enable interrupts on the HBA. */
	writel(readl(dd->mmio + HOST_CTL) | HOST_IRQ_EN,
					dd->mmio + HOST_CTL);
	return rv;
}