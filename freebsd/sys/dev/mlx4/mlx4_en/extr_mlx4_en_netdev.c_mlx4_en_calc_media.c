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
struct TYPE_4__ {int transceiver; int link_speed; } ;
struct mlx4_en_priv {scalar_t__ last_link_state; TYPE_1__* prof; TYPE_2__ port_state; } ;
struct TYPE_3__ {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_100_T ; 
 int IFM_10G_CX4 ; 
 int IFM_10G_SR ; 
 int IFM_40G_CR4 ; 
 int IFM_ETHER ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 scalar_t__ MLX4_DEV_EVENT_PORT_DOWN ; 

__attribute__((used)) static int mlx4_en_calc_media(struct mlx4_en_priv *priv)
{
	int trans_type;
	int active;

	active = IFM_ETHER;
	if (priv->last_link_state == MLX4_DEV_EVENT_PORT_DOWN)
		return (active);
	active |= IFM_FDX;
	trans_type = priv->port_state.transceiver;
	/* XXX I don't know all of the transceiver values. */
	switch (priv->port_state.link_speed) {
	case 100:
		active |= IFM_100_T;
		break;
	case 1000:
		active |= IFM_1000_T;
		break;
	case 10000:
		if (trans_type > 0 && trans_type <= 0xC)
			active |= IFM_10G_SR;
		else if (trans_type == 0x80 || trans_type == 0)
			active |= IFM_10G_CX4;
		break;
	case 40000:
		active |= IFM_40G_CR4;
		break;
	}
	if (priv->prof->tx_pause)
		active |= IFM_ETH_TXPAUSE;
	if (priv->prof->rx_pause)
		active |= IFM_ETH_RXPAUSE;

	return (active);
}