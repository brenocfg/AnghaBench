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
struct usb_ether {int dummy; } ;
struct ifnet {int dummy; } ;
struct aue_softc {int sc_flags; struct usb_ether sc_ue; } ;
struct aue_rxpkt {int /*<<< orphan*/  aue_rxstat; } ;
typedef  int /*<<< orphan*/  stat ;

/* Variables and functions */
 int AUE_FLAG_VER_2 ; 
 int /*<<< orphan*/  AUE_RXSTAT_MASK ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int /*<<< orphan*/  ETHER_CRC_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_rxbuf (struct usb_ether*,struct usb_page_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uether_rxflush (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int,struct aue_rxpkt*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct aue_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aue_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct aue_softc *sc = usbd_xfer_softc(xfer);
	struct usb_ether *ue = &sc->sc_ue;
	struct ifnet *ifp = uether_getifp(ue);
	struct aue_rxpkt stat;
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);
	pc = usbd_xfer_get_frame(xfer, 0);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "received %d bytes\n", actlen);

		if (sc->sc_flags & AUE_FLAG_VER_2) {

			if (actlen == 0) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				goto tr_setup;
			}
		} else {

			if (actlen <= (int)(sizeof(stat) + ETHER_CRC_LEN)) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				goto tr_setup;
			}
			usbd_copy_out(pc, actlen - sizeof(stat), &stat,
			    sizeof(stat));

			/*
			 * turn off all the non-error bits in the rx status
			 * word:
			 */
			stat.aue_rxstat &= AUE_RXSTAT_MASK;
			if (stat.aue_rxstat) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				goto tr_setup;
			}
			/* No errors; receive the packet. */
			actlen -= (sizeof(stat) + ETHER_CRC_LEN);
		}
		uether_rxbuf(ue, pc, 0, actlen);

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		uether_rxflush(ue);
		return;

	default:			/* Error */
		DPRINTF("bulk read error, %s\n",
		    usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}