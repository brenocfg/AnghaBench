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
struct urb {int /*<<< orphan*/  setup_packet; scalar_t__ transfer_buffer_length; int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; struct sk_buff* context; } ;
struct sk_buff {scalar_t__ dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  err_tx; int /*<<< orphan*/  byte_tx; } ;
struct hci_dev {TYPE_1__ stat; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct btusb_data {int /*<<< orphan*/  txlock; int /*<<< orphan*/  tx_in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btusb_tx_complete(struct urb *urb)
{
	struct sk_buff *skb = urb->context;
	struct hci_dev *hdev = (struct hci_dev *)skb->dev;
	struct btusb_data *data = hci_get_drvdata(hdev);
	unsigned long flags;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		goto done;

	if (!urb->status)
		hdev->stat.byte_tx += urb->transfer_buffer_length;
	else
		hdev->stat.err_tx++;

done:
	spin_lock_irqsave(&data->txlock, flags);
	data->tx_in_flight--;
	spin_unlock_irqrestore(&data->txlock, flags);

	kfree(urb->setup_packet);

	kfree_skb(skb);
}