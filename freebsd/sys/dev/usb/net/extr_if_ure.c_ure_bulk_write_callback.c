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
typedef  int /*<<< orphan*/  txpkt ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ure_txpkt {int /*<<< orphan*/  ure_pktlen; } ;
struct ure_softc {int sc_flags; int /*<<< orphan*/  sc_ue; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int URE_FLAG_LINK ; 
 int URE_TKPKT_TX_FS ; 
 int URE_TKPKT_TX_LS ; 
 int URE_TXPKT_LEN_MASK ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memset (struct ure_txpkt*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int,struct ure_txpkt*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ure_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
ure_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ure_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct usb_page_cache *pc;
	struct mbuf *m;
	struct ure_txpkt txpkt;
	int len, pos;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "transfer complete\n");
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		if ((sc->sc_flags & URE_FLAG_LINK) == 0 ||
		    (ifp->if_drv_flags & IFF_DRV_OACTIVE) != 0) {
			/*
			 * don't send anything if there is no link !
			 */
			return;
		}
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;
		pos = 0;
		len = m->m_pkthdr.len;
		pc = usbd_xfer_get_frame(xfer, 0);
		memset(&txpkt, 0, sizeof(txpkt));
		txpkt.ure_pktlen = htole32((len & URE_TXPKT_LEN_MASK) |
		    URE_TKPKT_TX_FS | URE_TKPKT_TX_LS);
		usbd_copy_in(pc, pos, &txpkt, sizeof(txpkt));
		pos += sizeof(txpkt);
		usbd_m_copy_in(pc, pos, m, 0, m->m_pkthdr.len);
		pos += m->m_pkthdr.len;

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		/*
		 * If there's a BPF listener, bounce a copy
		 * of this frame to him.
		 */
		BPF_MTAP(ifp, m);

		m_freem(m);

		/* Set frame length. */
		usbd_xfer_set_frame_len(xfer, 0, pos);

		usbd_transfer_submit(xfer);
		ifp->if_drv_flags |= IFF_DRV_OACTIVE;
		return;
	default:			/* Error */
		DPRINTFN(11, "transfer error, %s\n",
		    usbd_errstr(error));

		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}