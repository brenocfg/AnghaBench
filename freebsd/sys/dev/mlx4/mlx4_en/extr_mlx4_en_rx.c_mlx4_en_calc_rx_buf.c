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
struct net_device {int if_mtu; } ;
struct mlx4_en_priv {int rx_mb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int ETH_FCS_LEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int MCLBYTES ; 
 int MJUM16BYTES ; 
 int MJUM9BYTES ; 
 int MJUMPAGESIZE ; 
 int MLX4_NET_IP_ALIGN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,unsigned int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

void mlx4_en_calc_rx_buf(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int eff_mtu = dev->if_mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN +
	    MLX4_NET_IP_ALIGN;

	if (eff_mtu > MJUM16BYTES) {
		en_err(priv, "MTU(%u) is too big\n", (unsigned)dev->if_mtu);
                eff_mtu = MJUM16BYTES;
        } else if (eff_mtu > MJUM9BYTES) {
                eff_mtu = MJUM16BYTES;
        } else if (eff_mtu > MJUMPAGESIZE) {
                eff_mtu = MJUM9BYTES;
        } else if (eff_mtu > MCLBYTES) {
                eff_mtu = MJUMPAGESIZE;
        } else {
                eff_mtu = MCLBYTES;
        }

	priv->rx_mb_size = eff_mtu;

	en_dbg(DRV, priv, "Effective RX MTU: %d bytes\n", eff_mtu);
}