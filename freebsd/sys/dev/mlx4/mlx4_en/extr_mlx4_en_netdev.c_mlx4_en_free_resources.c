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
struct mlx4_en_priv {int tx_ring_num; int rx_ring_num; int /*<<< orphan*/  stat_ctx; int /*<<< orphan*/ * stat_sysctl; scalar_t__* rx_cq; TYPE_2__* prof; scalar_t__* rx_ring; scalar_t__* tx_cq; scalar_t__* tx_ring; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_ring_size; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rx_cpu_rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_en_destroy_cq (struct mlx4_en_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_en_destroy_rx_ring (struct mlx4_en_priv*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_destroy_tx_ring (struct mlx4_en_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

void mlx4_en_free_resources(struct mlx4_en_priv *priv)
{
	int i;

#ifdef CONFIG_RFS_ACCEL
	if (priv->dev->rx_cpu_rmap) {
		free_irq_cpu_rmap(priv->dev->rx_cpu_rmap);
		priv->dev->rx_cpu_rmap = NULL;
	}
#endif

	for (i = 0; i < priv->tx_ring_num; i++) {
		if (priv->tx_ring && priv->tx_ring[i])
			mlx4_en_destroy_tx_ring(priv, &priv->tx_ring[i]);
		if (priv->tx_cq && priv->tx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->tx_cq[i]);
	}

	for (i = 0; i < priv->rx_ring_num; i++) {
		if (priv->rx_ring[i])
			mlx4_en_destroy_rx_ring(priv, &priv->rx_ring[i],
				priv->prof->rx_ring_size);
		if (priv->rx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->rx_cq[i]);
	}

	if (priv->stat_sysctl != NULL)
		sysctl_ctx_free(&priv->stat_ctx);
}