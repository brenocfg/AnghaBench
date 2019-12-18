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
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {void* dev; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;
struct btusb_data {TYPE_1__* isoc_tx_ep; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_MAX_ISOC_FRAMES ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct urb* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  __fill_isoc_descriptor (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btusb_isoc_tx_complete ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urb *alloc_isoc_urb(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct urb *urb;
	unsigned int pipe;

	if (!data->isoc_tx_ep)
		return ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(BTUSB_MAX_ISOC_FRAMES, GFP_KERNEL);
	if (!urb)
		return ERR_PTR(-ENOMEM);

	pipe = usb_sndisocpipe(data->udev, data->isoc_tx_ep->bEndpointAddress);

	usb_fill_int_urb(urb, data->udev, pipe,
			 skb->data, skb->len, btusb_isoc_tx_complete,
			 skb, data->isoc_tx_ep->bInterval);

	urb->transfer_flags  = URB_ISO_ASAP;

	__fill_isoc_descriptor(urb, skb->len,
			       le16_to_cpu(data->isoc_tx_ep->wMaxPacketSize));

	skb->dev = (void *)hdev;

	return urb;
}