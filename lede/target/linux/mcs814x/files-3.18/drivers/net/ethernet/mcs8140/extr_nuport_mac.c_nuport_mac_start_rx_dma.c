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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nuport_mac_priv {int rx_addr; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RX_ALLOC_SIZE ; 
 int /*<<< orphan*/  RX_BUFFER_ADDR ; 
 int RX_DMA_ENABLE ; 
 int /*<<< orphan*/  RX_START_DMA ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int nuport_mac_start_rx_dma(struct nuport_mac_priv *priv,
					struct sk_buff *skb)
{
	u32 reg;
	unsigned int timeout = 2048;

	while (timeout--) {
		reg = nuport_mac_readl(RX_START_DMA);
		if (!(reg & RX_DMA_ENABLE)) {
			netdev_dbg(priv->dev, "dma ready\n");
			break;
		}
		cpu_relax();
	}

	if (!timeout)
		return -EBUSY;

	priv->rx_addr = dma_map_single(&priv->pdev->dev, skb->data,
				RX_ALLOC_SIZE, DMA_FROM_DEVICE);
	if (dma_mapping_error(&priv->pdev->dev, priv->rx_addr))
		return -ENOMEM;

	nuport_mac_writel(priv->rx_addr, RX_BUFFER_ADDR);
	wmb();
	nuport_mac_writel(RX_DMA_ENABLE, RX_START_DMA);

	return 0;
}