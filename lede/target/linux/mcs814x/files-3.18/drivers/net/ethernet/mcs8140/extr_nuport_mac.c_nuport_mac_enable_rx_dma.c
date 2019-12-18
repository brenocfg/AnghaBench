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
typedef  int /*<<< orphan*/  u32 ;
struct nuport_mac_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DMA_ENH ; 
 int /*<<< orphan*/  RX_DMA_INT_ENABLE ; 
 int /*<<< orphan*/  nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nuport_mac_enable_rx_dma(struct nuport_mac_priv *priv)
{
	u32 reg;

	reg = nuport_mac_readl(RX_DMA_ENH);
	reg |= RX_DMA_INT_ENABLE;
	nuport_mac_writel(reg, RX_DMA_ENH);
}