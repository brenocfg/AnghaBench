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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct nuport_mac_priv {int tx_addr; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TX_BUFFER_ADDR ; 
 int TX_DMA_ENABLE ; 
 int TX_DMA_END_FRAME ; 
 int /*<<< orphan*/  TX_DMA_ENH ; 
 int TX_DMA_ENH_ENABLE ; 
 int TX_DMA_START_FRAME ; 
 int /*<<< orphan*/  TX_PKT_BYTES ; 
 int /*<<< orphan*/  TX_START_DMA ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int nuport_mac_start_tx_dma(struct nuport_mac_priv *priv,
					struct sk_buff *skb)
{
	u32 reg;
	unsigned int timeout = 2048;

	while (timeout--) {
		reg = nuport_mac_readl(TX_START_DMA);
		if (!(reg & TX_DMA_ENABLE)) {
			netdev_dbg(priv->dev, "dma ready\n");
			break;
		}
		cpu_relax();
	}

	if (!timeout)
		return -EBUSY;

	priv->tx_addr = dma_map_single(&priv->pdev->dev, skb->data,
			skb->len, DMA_TO_DEVICE);
	if (dma_mapping_error(&priv->pdev->dev, priv->tx_addr))
		return -ENOMEM;

	/* enable enhanced mode */
	nuport_mac_writel(TX_DMA_ENH_ENABLE, TX_DMA_ENH);
	nuport_mac_writel(priv->tx_addr, TX_BUFFER_ADDR);
	nuport_mac_writel((skb->len) - 1, TX_PKT_BYTES);
	wmb();
	reg = TX_DMA_ENABLE | TX_DMA_START_FRAME | TX_DMA_END_FRAME;
	nuport_mac_writel(reg, TX_START_DMA);

	return 0;
}