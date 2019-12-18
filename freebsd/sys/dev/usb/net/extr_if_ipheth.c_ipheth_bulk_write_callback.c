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
typedef  size_t uint8_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_2__ {size_t len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ipheth_softc {struct mbuf** sc_tx_buf; int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 size_t IPHETH_BUF_SIZE ; 
 size_t IPHETH_TX_FRAMES_MAX ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipheth_free_queue (struct mbuf**,size_t) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_frame_zero (struct usb_page_cache*,size_t,size_t) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,size_t) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,size_t,size_t) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_offset (struct usb_xfer*,size_t,size_t) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,size_t) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ipheth_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipheth_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ipheth_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct usb_page_cache *pc;
	struct mbuf *m;
	uint8_t x;
	int actlen;
	int aframes;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTFN(1, "\n");

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "transfer complete: %u bytes in %u frames\n",
		    actlen, aframes);

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		/* free all previous TX buffers */
		ipheth_free_queue(sc->sc_tx_buf, IPHETH_TX_FRAMES_MAX);

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		for (x = 0; x != IPHETH_TX_FRAMES_MAX; x++) {

			IFQ_DRV_DEQUEUE(&ifp->if_snd, m);

			if (m == NULL)
				break;

			usbd_xfer_set_frame_offset(xfer,
			    x * IPHETH_BUF_SIZE, x);

			pc = usbd_xfer_get_frame(xfer, x);

			sc->sc_tx_buf[x] = m;

			if (m->m_pkthdr.len > IPHETH_BUF_SIZE)
				m->m_pkthdr.len = IPHETH_BUF_SIZE;

			usbd_m_copy_in(pc, 0, m, 0, m->m_pkthdr.len);

			usbd_xfer_set_frame_len(xfer, x, IPHETH_BUF_SIZE);

			if (IPHETH_BUF_SIZE != m->m_pkthdr.len) {
				usbd_frame_zero(pc, m->m_pkthdr.len,
					IPHETH_BUF_SIZE - m->m_pkthdr.len);
			}

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
		ipheth_free_queue(sc->sc_tx_buf, IPHETH_TX_FRAMES_MAX);

		/* count output errors */
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}