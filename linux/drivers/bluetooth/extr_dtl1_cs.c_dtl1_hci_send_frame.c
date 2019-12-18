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
struct sk_buff {int len; } ;
struct nsh {int type; int len; scalar_t__ zero; } ;
struct TYPE_2__ {int /*<<< orphan*/  sco_tx; int /*<<< orphan*/  acl_tx; int /*<<< orphan*/  cmd_tx; } ;
struct hci_dev {TYPE_1__ stat; } ;
struct dtl1_info {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int EILSEQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 
 scalar_t__ NSHL ; 
 struct sk_buff* bt_skb_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtl1_write_wakeup (struct dtl1_info*) ; 
 struct dtl1_info* hci_get_drvdata (struct hci_dev*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct nsh*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int dtl1_hci_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct dtl1_info *info = hci_get_drvdata(hdev);
	struct sk_buff *s;
	struct nsh nsh;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		nsh.type = 0x81;
		break;
	case HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		nsh.type = 0x82;
		break;
	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		nsh.type = 0x83;
		break;
	default:
		return -EILSEQ;
	}

	nsh.zero = 0;
	nsh.len = skb->len;

	s = bt_skb_alloc(NSHL + skb->len + 1, GFP_ATOMIC);
	if (!s)
		return -ENOMEM;

	skb_reserve(s, NSHL);
	skb_copy_from_linear_data(skb, skb_put(s, skb->len), skb->len);
	if (skb->len & 0x0001)
		skb_put_u8(s, 0);	/* PAD */

	/* Prepend skb with Nokia frame header and queue */
	memcpy(skb_push(s, NSHL), &nsh, NSHL);
	skb_queue_tail(&(info->txq), s);

	dtl1_write_wakeup(info);

	kfree_skb(skb);

	return 0;
}