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
typedef  int u8 ;
struct usb_ctrlrequest {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct urb {int /*<<< orphan*/  setup_packet; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; void* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sco_tx; int /*<<< orphan*/  acl_tx; int /*<<< orphan*/  cmd_tx; } ;
struct hci_dev {TYPE_1__ stat; int /*<<< orphan*/  name; } ;
struct bpa10x_data {int /*<<< orphan*/  tx_anchor; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EILSEQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 
 int /*<<< orphan*/  USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpa10x_tx_complete ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,struct urb*) ; 
 struct bpa10x_data* hci_get_drvdata (struct hci_dev*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct usb_ctrlrequest* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_fill_control_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int bpa10x_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct bpa10x_data *data = hci_get_drvdata(hdev);
	struct usb_ctrlrequest *dr;
	struct urb *urb;
	unsigned int pipe;
	int err;

	BT_DBG("%s", hdev->name);

	skb->dev = (void *) hdev;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return -ENOMEM;

	/* Prepend skb with frame type */
	*(u8 *)skb_push(skb, 1) = hci_skb_pkt_type(skb);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		dr = kmalloc(sizeof(*dr), GFP_KERNEL);
		if (!dr) {
			usb_free_urb(urb);
			return -ENOMEM;
		}

		dr->bRequestType = USB_TYPE_VENDOR;
		dr->bRequest     = 0;
		dr->wIndex       = 0;
		dr->wValue       = 0;
		dr->wLength      = __cpu_to_le16(skb->len);

		pipe = usb_sndctrlpipe(data->udev, 0x00);

		usb_fill_control_urb(urb, data->udev, pipe, (void *) dr,
				skb->data, skb->len, bpa10x_tx_complete, skb);

		hdev->stat.cmd_tx++;
		break;

	case HCI_ACLDATA_PKT:
		pipe = usb_sndbulkpipe(data->udev, 0x02);

		usb_fill_bulk_urb(urb, data->udev, pipe,
				skb->data, skb->len, bpa10x_tx_complete, skb);

		hdev->stat.acl_tx++;
		break;

	case HCI_SCODATA_PKT:
		pipe = usb_sndbulkpipe(data->udev, 0x02);

		usb_fill_bulk_urb(urb, data->udev, pipe,
				skb->data, skb->len, bpa10x_tx_complete, skb);

		hdev->stat.sco_tx++;
		break;

	default:
		usb_free_urb(urb);
		return -EILSEQ;
	}

	usb_anchor_urb(urb, &data->tx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	if (err < 0) {
		bt_dev_err(hdev, "urb %p submission failed", urb);
		kfree(urb->setup_packet);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}