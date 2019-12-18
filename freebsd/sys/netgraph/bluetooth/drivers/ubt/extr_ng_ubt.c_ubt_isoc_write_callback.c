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
struct ubt_softc {int /*<<< orphan*/  sc_scoq; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_BT_MBUFQ_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  UBT_INFO (struct ubt_softc*,char*,int) ; 
 int /*<<< orphan*/  UBT_NG_LOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_STAT_BYTES_SENT (struct ubt_softc*,int) ; 
 int /*<<< orphan*/  UBT_STAT_OERROR (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_STAT_PCKTS_SENT (struct ubt_softc*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int usbd_xfer_max_framelen (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 struct ubt_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
ubt_isoc_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ubt_softc	*sc = usbd_xfer_softc(xfer);
	struct usb_page_cache	*pc;
	struct mbuf		*m;
	int			n, space, offset;
	int			actlen, nframes;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, &nframes);
	pc = usbd_xfer_get_frame(xfer, 0);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		UBT_INFO(sc, "sent %d bytes to isoc-out pipe\n", actlen);
		UBT_STAT_BYTES_SENT(sc, actlen);
		UBT_STAT_PCKTS_SENT(sc);
		/* FALLTHROUGH */

	case USB_ST_SETUP:
send_next:
		offset = 0;
		space = usbd_xfer_max_framelen(xfer) * nframes;
		m = NULL;

		while (space > 0) {
			if (m == NULL) {
				UBT_NG_LOCK(sc);
				NG_BT_MBUFQ_DEQUEUE(&sc->sc_scoq, m);
				UBT_NG_UNLOCK(sc);

				if (m == NULL)
					break;
			}

			n = min(space, m->m_pkthdr.len);
			if (n > 0) {
				usbd_m_copy_in(pc, offset, m,0, n);
				m_adj(m, n);

				offset += n;
				space -= n;
			}

			if (m->m_pkthdr.len == 0)
				NG_FREE_M(m); /* sets m = NULL */
		}

		/* Put whatever is left from mbuf back on queue */
		if (m != NULL) {
			UBT_NG_LOCK(sc);
			NG_BT_MBUFQ_PREPEND(&sc->sc_scoq, m);
			UBT_NG_UNLOCK(sc);
		}

		/*
		 * Calculate sizes for isoc frames.
		 * Note that offset could be 0 at this point (i.e. we have
		 * nothing to send). That is fine, as we have isoc. transfers
		 * going in both directions all the time. In this case it
		 * would be just empty isoc. transfer.
		 */

		for (n = 0; n < nframes; n ++) {
			usbd_xfer_set_frame_len(xfer, n,
			    min(offset, usbd_xfer_max_framelen(xfer)));
			offset -= usbd_xfer_frame_len(xfer, n);
		}

		usbd_transfer_submit(xfer);
		break;

	default: /* Error */
		if (error != USB_ERR_CANCELLED) {
			UBT_STAT_OERROR(sc);
			goto send_next;
		}

		/* transfer cancelled */
		break;
	}
}