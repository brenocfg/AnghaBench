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
struct urb {int dummy; } ;
struct sk_buff {void* dev; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;
struct btusb_data {int /*<<< orphan*/  udev; TYPE_1__* bulk_tx_ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct urb* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  btusb_tx_complete ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urb *alloc_bulk_urb(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct urb *urb;
	unsigned int pipe;

	if (!data->bulk_tx_ep)
		return ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return ERR_PTR(-ENOMEM);

	pipe = usb_sndbulkpipe(data->udev, data->bulk_tx_ep->bEndpointAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe,
			  skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (void *)hdev;

	return urb;
}