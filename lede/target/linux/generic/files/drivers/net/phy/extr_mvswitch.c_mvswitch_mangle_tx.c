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
typedef  int u16 ;
struct sk_buff {int len; char* data; int mac_header; } ;
struct net_device {int /*<<< orphan*/  name; struct mvswitch_priv* phy_ptr; } ;
struct mvswitch_priv {int* vlans; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MV_HEADER_PORTS_M ; 
 int MV_HEADER_PORTS_S ; 
 scalar_t__ MV_HEADER_SIZE ; 
 int MV_HEADER_VLAN_M ; 
 int MV_HEADER_VLAN_S ; 
 int MV_TRAILER_FLAGS_S ; 
 int MV_TRAILER_OVERRIDE ; 
 int MV_TRAILER_PORTS_M ; 
 int MV_TRAILER_PORTS_S ; 
 int MV_TRAILER_SIZE ; 
 scalar_t__ __vlan_get_tag (struct sk_buff*,int*) ; 
 scalar_t__ __vlan_hwaccel_get_tag (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 char* skb_push (struct sk_buff*,scalar_t__) ; 
 char* skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *
mvswitch_mangle_tx(struct net_device *dev, struct sk_buff *skb)
{
	struct mvswitch_priv *priv;
	char *buf = NULL;
	u16 vid;

	priv = dev->phy_ptr;
	if (unlikely(!priv))
		goto error;

	if (unlikely(skb->len < 16))
		goto error;

#ifdef HEADER_MODE
	if (__vlan_hwaccel_get_tag(skb, &vid))
		goto error;

	if (skb_cloned(skb) || (skb->len <= 62) || (skb_headroom(skb) < MV_HEADER_SIZE)) {
		if (pskb_expand_head(skb, MV_HEADER_SIZE, (skb->len < 62 ? 62 - skb->len : 0), GFP_ATOMIC))
			goto error_expand;
		if (skb->len < 62)
			skb->len = 62;
	}
	buf = skb_push(skb, MV_HEADER_SIZE);
#else
	if (__vlan_get_tag(skb, &vid))
		goto error;

	if (unlikely((vid > 15 || !priv->vlans[vid])))
		goto error;

	if (skb->len <= 64) {
		if (pskb_expand_head(skb, 0, 64 + MV_TRAILER_SIZE - skb->len, GFP_ATOMIC))
			goto error_expand;

		buf = skb->data + 64;
		skb->len = 64 + MV_TRAILER_SIZE;
	} else {
		if (skb_cloned(skb) || unlikely(skb_tailroom(skb) < 4)) {
			if (pskb_expand_head(skb, 0, 4, GFP_ATOMIC))
				goto error_expand;
		}
		buf = skb_put(skb, 4);
	}

	/* move the ethernet header 4 bytes forward, overwriting the vlan tag */
	memmove(skb->data + 4, skb->data, 12);
	skb->data += 4;
	skb->len -= 4;
	skb->mac_header += 4;
#endif

	if (!buf)
		goto error;


#ifdef HEADER_MODE
	/* prepend the tag */
	*((__be16 *) buf) = cpu_to_be16(
		((vid << MV_HEADER_VLAN_S) & MV_HEADER_VLAN_M) |
		((priv->vlans[vid] << MV_HEADER_PORTS_S) & MV_HEADER_PORTS_M)
	);
#else
	/* append the tag */
	*((__be32 *) buf) = cpu_to_be32((
		(MV_TRAILER_OVERRIDE << MV_TRAILER_FLAGS_S) |
		((priv->vlans[vid] & MV_TRAILER_PORTS_M) << MV_TRAILER_PORTS_S)
	));
#endif

	return skb;

error_expand:
	if (net_ratelimit())
		printk("%s: failed to expand/update skb for the switch\n", dev->name);

error:
	/* any errors? drop the packet! */
	dev_kfree_skb_any(skb);
	return NULL;
}