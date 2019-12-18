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
typedef  int u32 ;
struct mtip_port {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ PORT_CMD ; 
 int PORT_CMD_FIS_RX ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_enable_fis(struct mtip_port *port, int enable)
{
	u32 tmp;

	/* enable FIS reception */
	tmp = readl(port->mmio + PORT_CMD);
	if (enable)
		writel(tmp | PORT_CMD_FIS_RX, port->mmio + PORT_CMD);
	else
		writel(tmp & ~PORT_CMD_FIS_RX, port->mmio + PORT_CMD);

	/* Flush */
	readl(port->mmio + PORT_CMD);

	return (((tmp & PORT_CMD_FIS_RX) == PORT_CMD_FIS_RX));
}