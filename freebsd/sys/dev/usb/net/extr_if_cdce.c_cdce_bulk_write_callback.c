#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_xfer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct mbuf {int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_data; TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ue_udev; } ;
struct cdce_softc {int sc_flags; TYPE_2__ sc_ue; struct mbuf** sc_tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int CDCE_FLAG_ZAURUS ; 
 size_t CDCE_FRAMES_MAX ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_MODE_HOST ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  cdce_free_queue (struct mbuf**,size_t) ; 
 int /*<<< orphan*/  cdce_m_crc32 (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_append (struct mbuf*,int,void*) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct ifnet* uether_getifp (TYPE_2__*) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,size_t) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct cdce_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cdce_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct cdce_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct mbuf *m;
	struct mbuf *mt;
	uint32_t crc;
	uint8_t x;
	int actlen, aframes;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTFN(1, "\n");

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "transfer complete: %u bytes in %u frames\n",
		    actlen, aframes);

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		/* free all previous TX buffers */
		cdce_free_queue(sc->sc_tx_buf, CDCE_FRAMES_MAX);

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		for (x = 0; x != CDCE_FRAMES_MAX; x++) {

			IFQ_DRV_DEQUEUE(&ifp->if_snd, m);

			if (m == NULL)
				break;

			if (sc->sc_flags & CDCE_FLAG_ZAURUS) {
				/*
				 * Zaurus wants a 32-bit CRC appended
				 * to every frame
				 */

				crc = cdce_m_crc32(m, 0, m->m_pkthdr.len);
				crc = htole32(crc);

				if (!m_append(m, 4, (void *)&crc)) {
					m_freem(m);
					if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
					continue;
				}
			}
			if (m->m_len != m->m_pkthdr.len) {
				mt = m_defrag(m, M_NOWAIT);
				if (mt == NULL) {
					m_freem(m);
					if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
					continue;
				}
				m = mt;
			}
			if (m->m_pkthdr.len > MCLBYTES) {
				m->m_pkthdr.len = MCLBYTES;
			}
			sc->sc_tx_buf[x] = m;
			usbd_xfer_set_frame_data(xfer, x, m->m_data, m->m_len);

			/*
			 * If there's a BPF listener, bounce a copy of
			 * this frame to him:
			 */
			BPF_MTAP(ifp, m);
		}
		if (x != 0) {
			usbd_xfer_set_frames(xfer, x);

			usbd_transfer_submit(xfer);
		}
		break;

	default:			/* Error */
		DPRINTFN(11, "transfer error, %s\n",
		    usbd_errstr(error));

		/* free all previous TX buffers */
		cdce_free_queue(sc->sc_tx_buf, CDCE_FRAMES_MAX);

		/* count output errors */
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

		if (error != USB_ERR_CANCELLED) {
			if (usbd_get_mode(sc->sc_ue.ue_udev) == USB_MODE_HOST) {
				/* try to clear stall first */
				usbd_xfer_set_stall(xfer);
			}
			goto tr_setup;
		}
		break;
	}
}