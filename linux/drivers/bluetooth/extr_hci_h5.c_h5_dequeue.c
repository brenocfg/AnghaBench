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
struct sk_buff {unsigned char const* data; int len; } ;
struct hci_uart {struct h5* priv; } ;
struct TYPE_2__ {scalar_t__ qlen; int /*<<< orphan*/  lock; } ;
struct h5 {scalar_t__ sleep; scalar_t__ tx_win; int /*<<< orphan*/  flags; TYPE_1__ unack; int /*<<< orphan*/  rel; int /*<<< orphan*/  timer; int /*<<< orphan*/  unrel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 scalar_t__ H5_ACK_TIMEOUT ; 
 scalar_t__ H5_AWAKE ; 
 int /*<<< orphan*/  H5_TX_ACK_REQ ; 
 scalar_t__ H5_WAKING_UP ; 
 int /*<<< orphan*/  HCI_3WIRE_ACK_PKT ; 
 int /*<<< orphan*/  HCI_3WIRE_LINK_PKT ; 
 int HZ ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 struct sk_buff* h5_prepare_pkt (struct hci_uart*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  hci_skb_pkt_type (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *h5_dequeue(struct hci_uart *hu)
{
	struct h5 *h5 = hu->priv;
	unsigned long flags;
	struct sk_buff *skb, *nskb;

	if (h5->sleep != H5_AWAKE) {
		const unsigned char wakeup_req[] = { 0x05, 0xfa };

		if (h5->sleep == H5_WAKING_UP)
			return NULL;

		h5->sleep = H5_WAKING_UP;
		BT_DBG("Sending wakeup request");

		mod_timer(&h5->timer, jiffies + HZ / 100);
		return h5_prepare_pkt(hu, HCI_3WIRE_LINK_PKT, wakeup_req, 2);
	}

	skb = skb_dequeue(&h5->unrel);
	if (skb) {
		nskb = h5_prepare_pkt(hu, hci_skb_pkt_type(skb),
				      skb->data, skb->len);
		if (nskb) {
			kfree_skb(skb);
			return nskb;
		}

		skb_queue_head(&h5->unrel, skb);
		BT_ERR("Could not dequeue pkt because alloc_skb failed");
	}

	spin_lock_irqsave_nested(&h5->unack.lock, flags, SINGLE_DEPTH_NESTING);

	if (h5->unack.qlen >= h5->tx_win)
		goto unlock;

	skb = skb_dequeue(&h5->rel);
	if (skb) {
		nskb = h5_prepare_pkt(hu, hci_skb_pkt_type(skb),
				      skb->data, skb->len);
		if (nskb) {
			__skb_queue_tail(&h5->unack, skb);
			mod_timer(&h5->timer, jiffies + H5_ACK_TIMEOUT);
			spin_unlock_irqrestore(&h5->unack.lock, flags);
			return nskb;
		}

		skb_queue_head(&h5->rel, skb);
		BT_ERR("Could not dequeue pkt because alloc_skb failed");
	}

unlock:
	spin_unlock_irqrestore(&h5->unack.lock, flags);

	if (test_bit(H5_TX_ACK_REQ, &h5->flags))
		return h5_prepare_pkt(hu, HCI_3WIRE_ACK_PKT, NULL, 0);

	return NULL;
}