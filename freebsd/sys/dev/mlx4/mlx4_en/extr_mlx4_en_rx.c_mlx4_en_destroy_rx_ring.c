#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * mbuf; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct mlx4_en_rx_ring {int /*<<< orphan*/  dma_tag; TYPE_2__* mbuf; TYPE_1__ spare; TYPE_3__ wqres; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 scalar_t__ TXBB_SIZE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_rx_ring*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_en_cleanup_filters (struct mlx4_en_priv*,struct mlx4_en_rx_ring*) ; 
 int /*<<< orphan*/  mlx4_en_unmap_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vfree (TYPE_2__*) ; 

void mlx4_en_destroy_rx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_rx_ring **pring,
			     u32 size)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_rx_ring *ring = *pring;
	uint32_t x;

	mlx4_en_unmap_buffer(&ring->wqres.buf);
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, size * sizeof(struct mlx4_en_rx_desc) + TXBB_SIZE);
	for (x = 0; x != size; x++)
		bus_dmamap_destroy(ring->dma_tag, ring->mbuf[x].dma_map);
	/* free spare mbuf, if any */
	if (ring->spare.mbuf != NULL) {
		bus_dmamap_sync(ring->dma_tag, ring->spare.dma_map,
		    BUS_DMASYNC_POSTREAD);
		bus_dmamap_unload(ring->dma_tag, ring->spare.dma_map);
		m_freem(ring->spare.mbuf);
	}
	bus_dmamap_destroy(ring->dma_tag, ring->spare.dma_map);
	vfree(ring->mbuf);
	bus_dma_tag_destroy(ring->dma_tag);
	kfree(ring);
	*pring = NULL;
#ifdef CONFIG_RFS_ACCEL
	mlx4_en_cleanup_filters(priv, ring);
#endif
}