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
struct mlx4_en_priv {int rx_ring_num; int tx_ring_num; int port_up; scalar_t__* tx_cq; scalar_t__* tx_ring; scalar_t__* rx_cq; scalar_t__* rx_ring; TYPE_1__* dev; struct mlx4_en_port_profile* prof; } ;
struct mlx4_en_port_profile {int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_cpu_rmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RX ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  TXBB_SIZE ; 
 int /*<<< orphan*/  alloc_irq_cpu_rmap (int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 scalar_t__ mlx4_en_create_cq (struct mlx4_en_priv*,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_en_create_rx_ring (struct mlx4_en_priv*,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_en_create_tx_ring (struct mlx4_en_priv*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx4_en_destroy_cq (struct mlx4_en_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_en_destroy_rx_ring (struct mlx4_en_priv*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_destroy_tx_ring (struct mlx4_en_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_en_sysctl_stat (struct mlx4_en_priv*) ; 

int mlx4_en_alloc_resources(struct mlx4_en_priv *priv)
{
	struct mlx4_en_port_profile *prof = priv->prof;
	int i;
	int node = 0;

	/* Create rx Rings */
	for (i = 0; i < priv->rx_ring_num; i++) {
		if (mlx4_en_create_cq(priv, &priv->rx_cq[i],
				      prof->rx_ring_size, i, RX, node))
			goto err;

		if (mlx4_en_create_rx_ring(priv, &priv->rx_ring[i],
					   prof->rx_ring_size, node))
			goto err;
	}

	/* Create tx Rings */
	for (i = 0; i < priv->tx_ring_num; i++) {
		if (mlx4_en_create_cq(priv, &priv->tx_cq[i],
				      prof->tx_ring_size, i, TX, node))
			goto err;

		if (mlx4_en_create_tx_ring(priv, &priv->tx_ring[i],
					   prof->tx_ring_size, TXBB_SIZE, node, i))
			goto err;
	}

#ifdef CONFIG_RFS_ACCEL
	priv->dev->rx_cpu_rmap = alloc_irq_cpu_rmap(priv->rx_ring_num);
	if (!priv->dev->rx_cpu_rmap)
		goto err;
#endif
        /* Re-create stat sysctls in case the number of rings changed. */
	mlx4_en_sysctl_stat(priv);
	return 0;

err:
	en_err(priv, "Failed to allocate NIC resources\n");
	for (i = 0; i < priv->rx_ring_num; i++) {
		if (priv->rx_ring[i])
			mlx4_en_destroy_rx_ring(priv, &priv->rx_ring[i],
						prof->rx_ring_size);
		if (priv->rx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->rx_cq[i]);
	}
	for (i = 0; i < priv->tx_ring_num; i++) {
		if (priv->tx_ring[i])
			mlx4_en_destroy_tx_ring(priv, &priv->tx_ring[i]);
		if (priv->tx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->tx_cq[i]);
	}
	priv->port_up = false;
	return -ENOMEM;
}