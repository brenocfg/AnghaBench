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
struct mlx4_en_tx_ring {scalar_t__ watchdog_time; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port_up; struct mlx4_en_tx_ring** tx_ring; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int ENOBUFS ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ MLX4_EN_WATCHDOG_TIMEOUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ mlx4_en_xmit (struct mlx4_en_priv*,int,struct mbuf**) ; 
 struct mlx4_en_priv* netdev_priv (struct ifnet*) ; 
 scalar_t__ ticks ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
mlx4_en_transmit_locked(struct ifnet *ifp, int tx_ind, struct mbuf *mb)
{
	struct mlx4_en_priv *priv = netdev_priv(ifp);
	struct mlx4_en_tx_ring *ring = priv->tx_ring[tx_ind];
	int err = 0;

	if (unlikely((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0 ||
	    READ_ONCE(priv->port_up) == 0)) {
		m_freem(mb);
		return (ENETDOWN);
	}

	if (mlx4_en_xmit(priv, tx_ind, &mb) != 0) {
		/* NOTE: m_freem() is NULL safe */
		m_freem(mb);
		err = ENOBUFS;
		if (ring->watchdog_time == 0)
			ring->watchdog_time = ticks + MLX4_EN_WATCHDOG_TIMEOUT;
	} else {
		ring->watchdog_time = 0;
	}
	return (err);
}