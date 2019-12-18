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
struct sk_buff {int dummy; } ;
struct net_device {struct ar8xxx_priv* phy_ptr; } ;
struct ar8xxx_priv {int /*<<< orphan*/  vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *
ar8216_mangle_tx(struct net_device *dev, struct sk_buff *skb)
{
	struct ar8xxx_priv *priv = dev->phy_ptr;
	unsigned char *buf;

	if (unlikely(!priv))
		goto error;

	if (!priv->vlan)
		goto send;

	if (unlikely(skb_headroom(skb) < 2)) {
		if (pskb_expand_head(skb, 2, 0, GFP_ATOMIC) < 0)
			goto error;
	}

	buf = skb_push(skb, 2);
	buf[0] = 0x10;
	buf[1] = 0x80;

send:
	return skb;

error:
	dev_kfree_skb_any(skb);
	return NULL;
}