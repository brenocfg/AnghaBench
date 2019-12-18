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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_ether {int dummy; } ;
struct mos_softc {struct usb_ether sc_ue; } ;
struct ifnet {int dummy; } ;
struct ether_header {int dummy; } ;
typedef  int /*<<< orphan*/  rxstat ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  MOS_DPRINTFN (char*,...) ; 
 int MOS_RXSTS_ALIGN_ERROR ; 
 int MOS_RXSTS_CRC_ERROR ; 
 int MOS_RXSTS_LARGE_FRAME ; 
 int MOS_RXSTS_SHORT_FRAME ; 
 int MOS_RXSTS_VALID ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_rxbuf (struct usb_ether*,struct usb_page_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uether_rxflush (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct mos_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mos_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct mos_softc *sc = usbd_xfer_softc(xfer);
	struct usb_ether *ue = &sc->sc_ue;
	struct ifnet *ifp = uether_getifp(ue);

	uint8_t rxstat = 0;
	uint32_t actlen;
	uint16_t pktlen = 0;
	struct usb_page_cache *pc;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);
	pc = usbd_xfer_get_frame(xfer, 0);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		MOS_DPRINTFN("actlen : %d", actlen);
		if (actlen <= 1) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			goto tr_setup;
		}
		/* evaluate status byte at the end */
		usbd_copy_out(pc, actlen - sizeof(rxstat), &rxstat,
		    sizeof(rxstat));

		if (rxstat != MOS_RXSTS_VALID) {
			MOS_DPRINTFN("erroneous frame received");
			if (rxstat & MOS_RXSTS_SHORT_FRAME)
				MOS_DPRINTFN("frame size less than 64 bytes");
			if (rxstat & MOS_RXSTS_LARGE_FRAME) {
				MOS_DPRINTFN("frame size larger than "
				    "1532 bytes");
			}
			if (rxstat & MOS_RXSTS_CRC_ERROR)
				MOS_DPRINTFN("CRC error");
			if (rxstat & MOS_RXSTS_ALIGN_ERROR)
				MOS_DPRINTFN("alignment error");
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			goto tr_setup;
		}
		/* Remember the last byte was used for the status fields */
		pktlen = actlen - 1;
		if (pktlen < sizeof(struct ether_header)) {
			MOS_DPRINTFN("error: pktlen %d is smaller "
			    "than ether_header %zd", pktlen,
			    sizeof(struct ether_header));
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			goto tr_setup;
		}
		uether_rxbuf(ue, pc, 0, actlen);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		uether_rxflush(ue);
		return;
	default:
		MOS_DPRINTFN("bulk read error, %s", usbd_errstr(error));
		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		MOS_DPRINTFN("start rx %i", usbd_xfer_max_len(xfer));
		return;
	}
}