#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct driver_data {TYPE_1__* port; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  svc_wait; int /*<<< orphan*/  flags; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_PF_EH_ACTIVE_BIT ; 
 int PORT_IRQ_CONNECT ; 
 int PORT_IRQ_HANDLED ; 
 int PORT_IRQ_IF_ERR ; 
 int PORT_IRQ_PHYRDY ; 
 int PORT_IRQ_TF_ERR ; 
 scalar_t__ PORT_SCR_ERR ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ mtip_check_surprise_removal (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void mtip_process_errors(struct driver_data *dd, u32 port_stat)
{
	if (unlikely(port_stat & PORT_IRQ_CONNECT)) {
		dev_warn(&dd->pdev->dev,
			"Clearing PxSERR.DIAG.x\n");
		writel((1 << 26), dd->port->mmio + PORT_SCR_ERR);
	}

	if (unlikely(port_stat & PORT_IRQ_PHYRDY)) {
		dev_warn(&dd->pdev->dev,
			"Clearing PxSERR.DIAG.n\n");
		writel((1 << 16), dd->port->mmio + PORT_SCR_ERR);
	}

	if (unlikely(port_stat & ~PORT_IRQ_HANDLED)) {
		dev_warn(&dd->pdev->dev,
			"Port stat errors %x unhandled\n",
			(port_stat & ~PORT_IRQ_HANDLED));
		if (mtip_check_surprise_removal(dd->pdev))
			return;
	}
	if (likely(port_stat & (PORT_IRQ_TF_ERR | PORT_IRQ_IF_ERR))) {
		set_bit(MTIP_PF_EH_ACTIVE_BIT, &dd->port->flags);
		wake_up_interruptible(&dd->port->svc_wait);
	}
}