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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; struct hci_dev* context; } ;
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btusb_data {int /*<<< orphan*/  udev; int /*<<< orphan*/  diag_anchor; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_DIAG_RUNNING ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,struct urb*,int) ; 
 struct sk_buff* bt_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_recv_diag (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void btusb_diag_complete(struct urb *urb)
{
	struct hci_dev *hdev = urb->context;
	struct btusb_data *data = hci_get_drvdata(hdev);
	int err;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	if (urb->status == 0) {
		struct sk_buff *skb;

		skb = bt_skb_alloc(urb->actual_length, GFP_ATOMIC);
		if (skb) {
			skb_put_data(skb, urb->transfer_buffer,
				     urb->actual_length);
			hci_recv_diag(hdev, skb);
		}
	} else if (urb->status == -ENOENT) {
		/* Avoid suspend failed when usb_kill_urb */
		return;
	}

	if (!test_bit(BTUSB_DIAG_RUNNING, &data->flags))
		return;

	usb_anchor_urb(urb, &data->diag_anchor);
	usb_mark_last_busy(data->udev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err < 0) {
		/* -EPERM: urb is being killed;
		 * -ENODEV: device got disconnected
		 */
		if (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p failed to resubmit (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	}
}