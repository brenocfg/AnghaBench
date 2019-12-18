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
struct sk_buff {int len; } ;
struct hci_uart {struct h5* priv; } ;
struct h5 {scalar_t__ state; int /*<<< orphan*/  unrel; int /*<<< orphan*/  rel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 scalar_t__ H5_ACTIVE ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int h5_enqueue(struct hci_uart *hu, struct sk_buff *skb)
{
	struct h5 *h5 = hu->priv;

	if (skb->len > 0xfff) {
		BT_ERR("Packet too long (%u bytes)", skb->len);
		kfree_skb(skb);
		return 0;
	}

	if (h5->state != H5_ACTIVE) {
		BT_ERR("Ignoring HCI data in non-active state");
		kfree_skb(skb);
		return 0;
	}

	switch (hci_skb_pkt_type(skb)) {
	case HCI_ACLDATA_PKT:
	case HCI_COMMAND_PKT:
		skb_queue_tail(&h5->rel, skb);
		break;

	case HCI_SCODATA_PKT:
		skb_queue_tail(&h5->unrel, skb);
		break;

	default:
		BT_ERR("Unknown packet type %u", hci_skb_pkt_type(skb));
		kfree_skb(skb);
		break;
	}

	return 0;
}