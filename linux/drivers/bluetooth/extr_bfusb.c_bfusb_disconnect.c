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
struct usb_interface {int dummy; } ;
struct hci_dev {int dummy; } ;
struct bfusb_data {struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct usb_interface*) ; 
 int /*<<< orphan*/  bfusb_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 struct bfusb_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfusb_disconnect(struct usb_interface *intf)
{
	struct bfusb_data *data = usb_get_intfdata(intf);
	struct hci_dev *hdev = data->hdev;

	BT_DBG("intf %p", intf);

	if (!hdev)
		return;

	usb_set_intfdata(intf, NULL);

	bfusb_close(hdev);

	hci_unregister_dev(hdev);
	hci_free_dev(hdev);
}