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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ubt_hci_event {int dummy; } ;

/* Variables and functions */
 int UBT_HCI_EVENT_SIZE (struct ubt_hci_event*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,struct ubt_hci_event*,int) ; 
 char* usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ubt_hci_event* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ubt_hci_event*) ; 

__attribute__((used)) static void
ubt_probe_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ubt_hci_event	*evt = usbd_xfer_softc(xfer);
	struct usb_page_cache	*pc;
	int			actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		if (actlen > UBT_HCI_EVENT_SIZE(evt))
			actlen = UBT_HCI_EVENT_SIZE(evt);
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, evt, actlen);
		/* OneShot mode */
		wakeup(evt);
		break;

        case USB_ST_SETUP:
submit_next:
		/* Try clear stall first */
		usbd_xfer_set_stall(xfer);
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:
		if (error != USB_ERR_CANCELLED) {
			printf("ng_ubt: interrupt transfer failed: %s\n",
				usbd_errstr(error));
			goto submit_next;
		}
		break;
	}
}