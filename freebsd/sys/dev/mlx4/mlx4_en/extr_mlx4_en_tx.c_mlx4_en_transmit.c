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
struct mlx4_en_tx_ring {int /*<<< orphan*/  tx_lock; } ;
struct mlx4_en_priv {scalar_t__ port_up; int tx_ring_num; struct mlx4_en_tx_ring** tx_ring; } ;
struct TYPE_2__ {int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mlx4_en_select_queue (struct ifnet*,struct mbuf*) ; 
 int mlx4_en_transmit_locked (struct ifnet*,int,struct mbuf*) ; 
 int /*<<< orphan*/  mlx4_en_xmit_poll (struct mlx4_en_priv*,int) ; 
 struct mlx4_en_priv* netdev_priv (struct ifnet*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int
mlx4_en_transmit(struct ifnet *dev, struct mbuf *m)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_tx_ring *ring;
	int i, err = 0;

	if (priv->port_up == 0) {
		m_freem(m);
		return (ENETDOWN);
	}

	/* Compute which queue to use */
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE) {
		i = (m->m_pkthdr.flowid % 128) % priv->tx_ring_num;
	}
	else {
		i = mlx4_en_select_queue(dev, m);
	}

	ring = priv->tx_ring[i];

	spin_lock(&ring->tx_lock);

	err = mlx4_en_transmit_locked(dev, i, m);
	spin_unlock(&ring->tx_lock);

	/* Poll CQ here */
	mlx4_en_xmit_poll(priv, i);

#if __FreeBSD_version >= 1100000
	if (unlikely(err != 0))
		if_inc_counter(dev, IFCOUNTER_IQDROPS, 1);
#endif
	return (err);
}