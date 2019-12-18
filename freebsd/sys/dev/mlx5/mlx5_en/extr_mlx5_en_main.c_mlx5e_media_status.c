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
struct TYPE_2__ {scalar_t__ tx_pauseframe_control; scalar_t__ rx_pauseframe_control; } ;
struct mlx5e_priv {int media_active_last; TYPE_1__ params; int /*<<< orphan*/  media_status_last; } ;
struct ifnet {struct mlx5e_priv* if_softc; } ;
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 

__attribute__((used)) static void
mlx5e_media_status(struct ifnet *dev, struct ifmediareq *ifmr)
{
	struct mlx5e_priv *priv = dev->if_softc;

	ifmr->ifm_status = priv->media_status_last;
	ifmr->ifm_active = priv->media_active_last |
	    (priv->params.rx_pauseframe_control ? IFM_ETH_RXPAUSE : 0) |
	    (priv->params.tx_pauseframe_control ? IFM_ETH_TXPAUSE : 0);

}