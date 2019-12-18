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
typedef  int /*<<< orphan*/  uint64_t ;
struct usb_xfer {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_ierrors; } ;
struct urtw_softc {int /*<<< orphan*/  sc_txstatus; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_ASSERT_LOCKED (struct urtw_softc*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  urtw_txstatus_eof (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 void* usbd_xfer_get_frame_buffer (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct urtw_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
urtw_bulk_tx_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct urtw_softc *sc = usbd_xfer_softc(xfer);
	struct ieee80211com *ic = &sc->sc_ic;
	void *dma_buf = usbd_xfer_get_frame_buffer(xfer, 0);

	URTW_ASSERT_LOCKED(sc);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		urtw_txstatus_eof(xfer);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
setup:
		memcpy(dma_buf, &sc->sc_txstatus, sizeof(uint64_t));
		usbd_xfer_set_frame_len(xfer, 0, sizeof(uint64_t));
		usbd_transfer_submit(xfer);
		break;
	default:
		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			counter_u64_add(ic->ic_ierrors, 1);
			goto setup;
		}
		break;
	}
}