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
struct usb_hci {int /*<<< orphan*/  hci_port; } ;
typedef  enum hci_usbev { ____Placeholder_hci_usbev } hci_usbev ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 

__attribute__((used)) static int
pci_xhci_dev_event(struct usb_hci *hci, enum hci_usbev evid, void *param)
{

	DPRINTF(("xhci device event port %d\r\n", hci->hci_port));
	return (0);
}