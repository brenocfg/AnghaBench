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
struct sk_buff {scalar_t__ data; } ;
struct hci_event_hdr {int evt; } ;
struct hci_dev {int dummy; } ;
struct btmtkuart_dev {int /*<<< orphan*/ * evt_skb; int /*<<< orphan*/  tx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTMTKUART_TX_WAIT_VND_EVT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCI_EV_VENDOR ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int hci_recv_frame (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmtkuart_recv_event(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);
	struct hci_event_hdr *hdr = (void *)skb->data;
	int err;

	/* Fix up the vendor event id with 0xff for vendor specific instead
	 * of 0xe4 so that event send via monitoring socket can be parsed
	 * properly.
	 */
	if (hdr->evt == 0xe4)
		hdr->evt = HCI_EV_VENDOR;

	/* When someone waits for the WMT event, the skb is being cloned
	 * and being processed the events from there then.
	 */
	if (test_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state)) {
		bdev->evt_skb = skb_clone(skb, GFP_KERNEL);
		if (!bdev->evt_skb) {
			err = -ENOMEM;
			goto err_out;
		}
	}

	err = hci_recv_frame(hdev, skb);
	if (err < 0)
		goto err_free_skb;

	if (hdr->evt == HCI_EV_VENDOR) {
		if (test_and_clear_bit(BTMTKUART_TX_WAIT_VND_EVT,
				       &bdev->tx_state)) {
			/* Barrier to sync with other CPUs */
			smp_mb__after_atomic();
			wake_up_bit(&bdev->tx_state, BTMTKUART_TX_WAIT_VND_EVT);
		}
	}

	return 0;

err_free_skb:
	kfree_skb(bdev->evt_skb);
	bdev->evt_skb = NULL;

err_out:
	return err;
}