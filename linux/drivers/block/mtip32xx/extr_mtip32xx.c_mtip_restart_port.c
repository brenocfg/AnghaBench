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
struct mtip_port {TYPE_2__* dd; scalar_t__ mmio; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  dd_flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 scalar_t__ PORT_CMD ; 
 int PORT_CMD_LIST_ON ; 
 scalar_t__ PORT_SCR_CTL ; 
 scalar_t__ PORT_SCR_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mtip_enable_engine (struct mtip_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtip_hba_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  mtip_init_port (struct mtip_port*) ; 
 int /*<<< orphan*/  mtip_start_port (struct mtip_port*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtip_restart_port(struct mtip_port *port)
{
	unsigned long timeout;

	/* Disable the DMA engine */
	mtip_enable_engine(port, 0);

	/* Chip quirk: wait up to 500ms for PxCMD.CR == 0 */
	timeout = jiffies + msecs_to_jiffies(500);
	while ((readl(port->mmio + PORT_CMD) & PORT_CMD_LIST_ON)
		 && time_before(jiffies, timeout))
		;

	if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		return;

	/*
	 * Chip quirk: escalate to hba reset if
	 * PxCMD.CR not clear after 500 ms
	 */
	if (readl(port->mmio + PORT_CMD) & PORT_CMD_LIST_ON) {
		dev_warn(&port->dd->pdev->dev,
			"PxCMD.CR not clear, escalating reset\n");

		if (mtip_hba_reset(port->dd))
			dev_err(&port->dd->pdev->dev,
				"HBA reset escalation failed.\n");

		/* 30 ms delay before com reset to quiesce chip */
		mdelay(30);
	}

	dev_warn(&port->dd->pdev->dev, "Issuing COM reset\n");

	/* Set PxSCTL.DET */
	writel(readl(port->mmio + PORT_SCR_CTL) |
			 1, port->mmio + PORT_SCR_CTL);
	readl(port->mmio + PORT_SCR_CTL);

	/* Wait 1 ms to quiesce chip function */
	timeout = jiffies + msecs_to_jiffies(1);
	while (time_before(jiffies, timeout))
		;

	if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		return;

	/* Clear PxSCTL.DET */
	writel(readl(port->mmio + PORT_SCR_CTL) & ~1,
			 port->mmio + PORT_SCR_CTL);
	readl(port->mmio + PORT_SCR_CTL);

	/* Wait 500 ms for bit 0 of PORT_SCR_STS to be set */
	timeout = jiffies + msecs_to_jiffies(500);
	while (((readl(port->mmio + PORT_SCR_STAT) & 0x01) == 0)
			 && time_before(jiffies, timeout))
		;

	if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		return;

	if ((readl(port->mmio + PORT_SCR_STAT) & 0x01) == 0)
		dev_warn(&port->dd->pdev->dev,
			"COM reset failed\n");

	mtip_init_port(port);
	mtip_start_port(port);

}