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
struct net_device {int /*<<< orphan*/  dev; } ;
struct fe_rx_ring {int rx_ring_size; int rx_phys; int rx_calc_idx; TYPE_1__* rx_dma; int /*<<< orphan*/  rx_buf_size; scalar_t__* rx_data; int /*<<< orphan*/  frag_size; int /*<<< orphan*/  frag_cache; } ;
struct fe_priv {int flags; struct fe_rx_ring rx_ring; struct net_device* netdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {unsigned int rxd1; int /*<<< orphan*/  rxd2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int FE_FLAG_RX_2B_OFFSET ; 
 int FE_FLAG_RX_SG_DMA ; 
 int FE_PST_DRX_IDX0 ; 
 int /*<<< orphan*/  FE_REG_PDMA_RST_CFG ; 
 int /*<<< orphan*/  FE_REG_RX_BASE_PTR0 ; 
 int /*<<< orphan*/  FE_REG_RX_CALC_IDX0 ; 
 int /*<<< orphan*/  FE_REG_RX_MAX_CNT0 ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NET_IP_ALIGN ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  RX_DMA_LSO ; 
 int /*<<< orphan*/  RX_DMA_PLEN0 (int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 TYPE_1__* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fe_reg_w32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ page_frag_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int fe_alloc_rx(struct fe_priv *priv)
{
	struct net_device *netdev = priv->netdev;
	struct fe_rx_ring *ring = &priv->rx_ring;
	int i, pad;

	ring->rx_data = kcalloc(ring->rx_ring_size, sizeof(*ring->rx_data),
			GFP_KERNEL);
	if (!ring->rx_data)
		goto no_rx_mem;

	for (i = 0; i < ring->rx_ring_size; i++) {
		ring->rx_data[i] = page_frag_alloc(&ring->frag_cache,
						   ring->frag_size,
						   GFP_KERNEL);
		if (!ring->rx_data[i])
			goto no_rx_mem;
	}

	ring->rx_dma = dma_alloc_coherent(&netdev->dev,
			ring->rx_ring_size * sizeof(*ring->rx_dma),
			&ring->rx_phys,
			GFP_ATOMIC | __GFP_ZERO);
	if (!ring->rx_dma)
		goto no_rx_mem;

	if (priv->flags & FE_FLAG_RX_2B_OFFSET)
		pad = 0;
	else
		pad = NET_IP_ALIGN;
	for (i = 0; i < ring->rx_ring_size; i++) {
		dma_addr_t dma_addr = dma_map_single(&netdev->dev,
				ring->rx_data[i] + NET_SKB_PAD + pad,
				ring->rx_buf_size,
				DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(&netdev->dev, dma_addr)))
			goto no_rx_mem;
		ring->rx_dma[i].rxd1 = (unsigned int)dma_addr;

		if (priv->flags & FE_FLAG_RX_SG_DMA)
			ring->rx_dma[i].rxd2 = RX_DMA_PLEN0(ring->rx_buf_size);
		else
			ring->rx_dma[i].rxd2 = RX_DMA_LSO;
	}
	ring->rx_calc_idx = ring->rx_ring_size - 1;
	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();

	fe_reg_w32(ring->rx_phys, FE_REG_RX_BASE_PTR0);
	fe_reg_w32(ring->rx_ring_size, FE_REG_RX_MAX_CNT0);
	fe_reg_w32(ring->rx_calc_idx, FE_REG_RX_CALC_IDX0);
	fe_reg_w32(FE_PST_DRX_IDX0, FE_REG_PDMA_RST_CFG);

	return 0;

no_rx_mem:
	return -ENOMEM;
}