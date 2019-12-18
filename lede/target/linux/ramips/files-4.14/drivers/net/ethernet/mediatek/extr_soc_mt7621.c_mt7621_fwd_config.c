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
struct net_device {int features; } ;
struct fe_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7620A_GDMA1_FWD_CFG ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int fe_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7621_rxcsum_config (int) ; 
 int /*<<< orphan*/  mt7621_rxvlan_config (int) ; 
 struct net_device* priv_netdev (struct fe_priv*) ; 

__attribute__((used)) static int mt7621_fwd_config(struct fe_priv *priv)
{
	struct net_device *dev = priv_netdev(priv);

	fe_w32(fe_r32(MT7620A_GDMA1_FWD_CFG) & ~0xffff,
	       MT7620A_GDMA1_FWD_CFG);

	/* mt7621 doesn't have txcsum config */
	mt7621_rxcsum_config((dev->features & NETIF_F_RXCSUM));
	mt7621_rxvlan_config(dev->features & NETIF_F_HW_VLAN_CTAG_RX);

	return 0;
}