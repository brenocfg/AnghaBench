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
struct mbuf {int dummy; } ;
struct ipoib_dev_priv {scalar_t__ max_ib_mtu; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 scalar_t__ IB_GRH_BYTES ; 
 struct mbuf* ipoib_alloc_map_mb (struct ipoib_dev_priv*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct mbuf *
ipoib_alloc_rx_mb(struct ipoib_dev_priv *priv, int id)
{

	return ipoib_alloc_map_mb(priv, &priv->rx_ring[id],
	    priv->max_ib_mtu + IB_GRH_BYTES);
}