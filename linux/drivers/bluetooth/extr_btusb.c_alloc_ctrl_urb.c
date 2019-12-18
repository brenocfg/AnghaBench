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
struct usb_ctrlrequest {int /*<<< orphan*/  wLength; scalar_t__ wValue; scalar_t__ wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct urb {int dummy; } ;
struct sk_buff {void* dev; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;
struct btusb_data {int /*<<< orphan*/  udev; int /*<<< orphan*/  cmdreq; int /*<<< orphan*/  cmdreq_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct urb* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btusb_tx_complete ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 struct usb_ctrlrequest* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_control_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct urb *alloc_ctrl_urb(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct usb_ctrlrequest *dr;
	struct urb *urb;
	unsigned int pipe;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return ERR_PTR(-ENOMEM);

	dr = kmalloc(sizeof(*dr), GFP_KERNEL);
	if (!dr) {
		usb_free_urb(urb);
		return ERR_PTR(-ENOMEM);
	}

	dr->bRequestType = data->cmdreq_type;
	dr->bRequest     = data->cmdreq;
	dr->wIndex       = 0;
	dr->wValue       = 0;
	dr->wLength      = __cpu_to_le16(skb->len);

	pipe = usb_sndctrlpipe(data->udev, 0x00);

	usb_fill_control_urb(urb, data->udev, pipe, (void *)dr,
			     skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (void *)hdev;

	return urb;
}