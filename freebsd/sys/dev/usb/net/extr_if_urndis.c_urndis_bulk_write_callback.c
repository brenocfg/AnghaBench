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
struct urndis_softc {int /*<<< orphan*/  sc_ue; } ;
struct rndis_packet_msg {void* rm_datalen; void* rm_dataoffset; void* rm_len; void* rm_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  REMOTE_NDIS_PACKET_MSG ; 
 int /*<<< orphan*/  RNDIS_DATA_OFFSET ; 
 unsigned int RNDIS_TX_FRAMES_MAX ; 
 unsigned int RNDIS_TX_MAXLEN ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memset (struct rndis_packet_msg*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct rndis_packet_msg*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,unsigned int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_offset (struct usb_xfer*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,unsigned int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct urndis_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
urndis_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct rndis_packet_msg msg;
	struct urndis_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct mbuf *m;
	unsigned x;
	int actlen;
	int aframes;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTFN(1, "\n");

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "%u bytes in %u frames\n", actlen, aframes);

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		memset(&msg, 0, sizeof(msg));

		for (x = 0; x != RNDIS_TX_FRAMES_MAX; x++) {
			struct usb_page_cache *pc = usbd_xfer_get_frame(xfer, x);

			usbd_xfer_set_frame_offset(xfer, x * RNDIS_TX_MAXLEN, x);

next_pkt:
			IFQ_DRV_DEQUEUE(&ifp->if_snd, m);

			if (m == NULL)
				break;

			if ((m->m_pkthdr.len + sizeof(msg)) > RNDIS_TX_MAXLEN) {
				DPRINTF("Too big packet\n");
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

				/* Free buffer */
				m_freem(m);
				goto next_pkt;
			}
			msg.rm_type = htole32(REMOTE_NDIS_PACKET_MSG);
			msg.rm_len = htole32(sizeof(msg) + m->m_pkthdr.len);

			msg.rm_dataoffset = htole32(RNDIS_DATA_OFFSET);
			msg.rm_datalen = htole32(m->m_pkthdr.len);

			/* copy in all data */
			usbd_copy_in(pc, 0, &msg, sizeof(msg));
			usbd_m_copy_in(pc, sizeof(msg), m, 0, m->m_pkthdr.len);
			usbd_xfer_set_frame_len(xfer, x, sizeof(msg) + m->m_pkthdr.len);

			/*
			 * If there's a BPF listener, bounce a copy of
			 * this frame to him:
			 */
			BPF_MTAP(ifp, m);

			/* Free buffer */
			m_freem(m);
		}
		if (x != 0) {
			usbd_xfer_set_frames(xfer, x);
			usbd_transfer_submit(xfer);
		}
		break;

	default:			/* Error */
		DPRINTFN(11, "transfer error, %s\n", usbd_errstr(error));

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