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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ubt_softc {int /*<<< orphan*/  sc_aclq; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_BT_MBUFQ_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  UBT_INFO (struct ubt_softc*,char*,...) ; 
 int /*<<< orphan*/  UBT_NG_LOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_STAT_BYTES_SENT (struct ubt_softc*,int) ; 
 int /*<<< orphan*/  UBT_STAT_OERROR (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_STAT_PCKTS_SENT (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_WARN (struct ubt_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ubt_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ubt_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ubt_softc	*sc = usbd_xfer_softc(xfer);
	struct mbuf		*m;
	struct usb_page_cache	*pc;
	int			actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		UBT_INFO(sc, "sent %d bytes to bulk-out pipe\n", actlen);
		UBT_STAT_BYTES_SENT(sc, actlen);
		UBT_STAT_PCKTS_SENT(sc);
		/* FALLTHROUGH */

	case USB_ST_SETUP:
send_next:
		/* Get next mbuf, if any */
		UBT_NG_LOCK(sc);
		NG_BT_MBUFQ_DEQUEUE(&sc->sc_aclq, m);
		UBT_NG_UNLOCK(sc);

		if (m == NULL) {
			UBT_INFO(sc, "ACL data queue is empty\n");
			break; /* transfer completed */
		}

		/*
		 * Copy ACL data frame back to a linear USB transfer buffer
		 * and schedule transfer
		 */

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_m_copy_in(pc, 0, m, 0, m->m_pkthdr.len);
		usbd_xfer_set_frame_len(xfer, 0, m->m_pkthdr.len);

		UBT_INFO(sc, "bulk-out transfer has been started, len=%d\n",
			m->m_pkthdr.len);

		NG_FREE_M(m);

		usbd_transfer_submit(xfer);
		break;

	default: /* Error */
		if (error != USB_ERR_CANCELLED) {
			UBT_WARN(sc, "bulk-out transfer failed: %s\n",
				usbd_errstr(error));

			UBT_STAT_OERROR(sc);

			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto send_next;
		}
			/* transfer cancelled */
		break;
	}
}