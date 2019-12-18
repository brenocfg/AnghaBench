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
struct xilinx_dma_device {int /*<<< orphan*/  axi_clk; int /*<<< orphan*/  tx_clk; int /*<<< orphan*/  txs_clk; int /*<<< orphan*/  rx_clk; int /*<<< orphan*/  rxs_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdma_disable_allclks(struct xilinx_dma_device *xdev)
{
	clk_disable_unprepare(xdev->rxs_clk);
	clk_disable_unprepare(xdev->rx_clk);
	clk_disable_unprepare(xdev->txs_clk);
	clk_disable_unprepare(xdev->tx_clk);
	clk_disable_unprepare(xdev->axi_clk);
}