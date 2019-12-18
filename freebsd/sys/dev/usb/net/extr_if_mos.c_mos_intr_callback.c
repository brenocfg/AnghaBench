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
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct mos_softc {int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  MOS_DPRINTFN (char*,int) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct mos_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mos_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct mos_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct usb_page_cache *pc;
	uint32_t pkt;
	int actlen;

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);
	MOS_DPRINTFN("actlen %i", actlen);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &pkt, sizeof(pkt));
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		return;
	default:
		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}