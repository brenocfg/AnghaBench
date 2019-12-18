#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  m; } ;
struct TYPE_5__ {int /*<<< orphan*/  m; } ;
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
struct mlx4_en_tx_ring {size_t size; int /*<<< orphan*/  dma_tag; TYPE_2__ comp_lock; TYPE_1__ tx_lock; TYPE_3__* tx_info; int /*<<< orphan*/  buf_size; TYPE_4__ wqres; int /*<<< orphan*/  qpn; int /*<<< orphan*/  qp; int /*<<< orphan*/  bf; scalar_t__ bf_enabled; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_tx_ring*) ; 
 int /*<<< orphan*/  mlx4_bf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_en_unmap_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_qp_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_qp_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (TYPE_3__*) ; 

void mlx4_en_destroy_tx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_tx_ring **pring)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_tx_ring *ring = *pring;
	uint32_t x;
	en_dbg(DRV, priv, "Destroying tx ring, qpn: %d\n", ring->qpn);

	if (ring->bf_enabled)
		mlx4_bf_free(mdev->dev, &ring->bf);
	mlx4_qp_remove(mdev->dev, &ring->qp);
	mlx4_qp_free(mdev->dev, &ring->qp);
	mlx4_qp_release_range(priv->mdev->dev, ring->qpn, 1);
	mlx4_en_unmap_buffer(&ring->wqres.buf);
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, ring->buf_size);
	for (x = 0; x != ring->size; x++)
		bus_dmamap_destroy(ring->dma_tag, ring->tx_info[x].dma_map);
	vfree(ring->tx_info);
	mtx_destroy(&ring->tx_lock.m);
	mtx_destroy(&ring->comp_lock.m);
	bus_dma_tag_destroy(ring->dma_tag);
	kfree(ring);
	*pring = NULL;
}