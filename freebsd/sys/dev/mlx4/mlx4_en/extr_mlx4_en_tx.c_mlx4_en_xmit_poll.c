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
struct mlx4_en_tx_ring {int poll_cnt; int /*<<< orphan*/  comp_lock; } ;
struct mlx4_en_priv {scalar_t__ port_up; int /*<<< orphan*/  dev; struct mlx4_en_tx_ring** tx_ring; struct mlx4_en_cq** tx_cq; } ;
struct mlx4_en_cq {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int MLX4_EN_TX_POLL_MODER ; 
 scalar_t__ MLX4_EN_TX_POLL_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mlx4_en_process_tx_cq (int /*<<< orphan*/ ,struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mlx4_en_xmit_poll(struct mlx4_en_priv *priv, int tx_ind)
{
	struct mlx4_en_cq *cq = priv->tx_cq[tx_ind];
	struct mlx4_en_tx_ring *ring = priv->tx_ring[tx_ind];

	if (priv->port_up == 0)
		return;

	/* If we don't have a pending timer, set one up to catch our recent
	   post in case the interface becomes idle */
	if (!timer_pending(&cq->timer))
		mod_timer(&cq->timer, jiffies + MLX4_EN_TX_POLL_TIMEOUT);

	/* Poll the CQ every mlx4_en_TX_MODER_POLL packets */
	if ((++ring->poll_cnt & (MLX4_EN_TX_POLL_MODER - 1)) == 0)
		if (spin_trylock(&ring->comp_lock)) {
			mlx4_en_process_tx_cq(priv->dev, cq);
			spin_unlock(&ring->comp_lock);
		}
}