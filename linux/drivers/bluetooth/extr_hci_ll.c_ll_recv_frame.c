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
struct ll_struct {int /*<<< orphan*/  hcill_state; } ;
struct hci_uart {struct ll_struct* priv; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
#define  HCILL_GO_TO_SLEEP_ACK 131 
#define  HCILL_GO_TO_SLEEP_IND 130 
#define  HCILL_WAKE_UP_ACK 129 
#define  HCILL_WAKE_UP_IND 128 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ll_device_want_to_sleep (struct hci_uart*) ; 
 int /*<<< orphan*/  ll_device_want_to_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  ll_device_woke_up (struct hci_uart*) ; 

__attribute__((used)) static int ll_recv_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct ll_struct *ll = hu->priv;

	switch (hci_skb_pkt_type(skb)) {
	case HCILL_GO_TO_SLEEP_IND:
		BT_DBG("HCILL_GO_TO_SLEEP_IND packet");
		ll_device_want_to_sleep(hu);
		break;
	case HCILL_GO_TO_SLEEP_ACK:
		/* shouldn't happen */
		bt_dev_err(hdev, "received HCILL_GO_TO_SLEEP_ACK in state %ld",
			   ll->hcill_state);
		break;
	case HCILL_WAKE_UP_IND:
		BT_DBG("HCILL_WAKE_UP_IND packet");
		ll_device_want_to_wakeup(hu);
		break;
	case HCILL_WAKE_UP_ACK:
		BT_DBG("HCILL_WAKE_UP_ACK packet");
		ll_device_woke_up(hu);
		break;
	}

	kfree_skb(skb);
	return 0;
}