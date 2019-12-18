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
struct sk_buff {unsigned char* data; } ;
struct net_device {struct ar8xxx_priv* phy_ptr; } ;
struct ar8xxx_priv {int vlan_tagged; int* vlan_id; size_t* pvid; int /*<<< orphan*/  vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void
ar8216_mangle_rx(struct net_device *dev, struct sk_buff *skb)
{
	struct ar8xxx_priv *priv;
	unsigned char *buf;
	int port, vlan;

	priv = dev->phy_ptr;
	if (!priv)
		return;

	/* don't strip the header if vlan mode is disabled */
	if (!priv->vlan)
		return;

	/* strip header, get vlan id */
	buf = skb->data;
	skb_pull(skb, 2);

	/* check for vlan header presence */
	if ((buf[12 + 2] != 0x81) || (buf[13 + 2] != 0x00))
		return;

	port = buf[0] & 0x7;

	/* no need to fix up packets coming from a tagged source */
	if (priv->vlan_tagged & (1 << port))
		return;

	/* lookup port vid from local table, the switch passes an invalid vlan id */
	vlan = priv->vlan_id[priv->pvid[port]];

	buf[14 + 2] &= 0xf0;
	buf[14 + 2] |= vlan >> 8;
	buf[15 + 2] = vlan & 0xff;
}