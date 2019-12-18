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
struct rue_softc {int /*<<< orphan*/  sc_ue; } ;
struct rue_intrpkt {int /*<<< orphan*/  rue_col_cnt; int /*<<< orphan*/  rue_crcerr_cnt; int /*<<< orphan*/  rue_rxlost_cnt; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,struct rue_intrpkt*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct rue_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rue_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct rue_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct rue_intrpkt pkt;
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		if (ifp && (ifp->if_drv_flags & IFF_DRV_RUNNING) &&
		    actlen >= (int)sizeof(pkt)) {

			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_out(pc, 0, &pkt, sizeof(pkt));

			if_inc_counter(ifp, IFCOUNTER_IERRORS, pkt.rue_rxlost_cnt);
			if_inc_counter(ifp, IFCOUNTER_IERRORS, pkt.rue_crcerr_cnt);
			if_inc_counter(ifp, IFCOUNTER_COLLISIONS, pkt.rue_col_cnt);
		}
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}