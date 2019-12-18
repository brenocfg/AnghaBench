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
struct TYPE_2__ {int len; int csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int if_capabilities; int /*<<< orphan*/  if_snd; } ;
struct axe_softc {int sc_flags; int /*<<< orphan*/  sc_ue; } ;
struct axe_sframe_hdr {int len; int ilen; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int AXE_CSUM_FEATURES ; 
 int AXE_FLAG_LINK ; 
 int /*<<< orphan*/  AXE_IS_178_FAMILY (struct axe_softc*) ; 
 int AXE_TX_CSUM_DIS ; 
 int AXE_TX_CSUM_PSEUDO_HDR ; 
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int IFCAP_TXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int htole16 (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int,struct axe_sframe_hdr*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_offset (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct axe_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
axe_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct axe_softc *sc = usbd_xfer_softc(xfer);
	struct axe_sframe_hdr hdr;
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct usb_page_cache *pc;
	struct mbuf *m;
	int nframes, pos;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "transfer complete\n");
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		if ((sc->sc_flags & AXE_FLAG_LINK) == 0 ||
		    (ifp->if_drv_flags & IFF_DRV_OACTIVE) != 0) {
			/*
			 * Don't send anything if there is no link or
			 * controller is busy.
			 */
			return;
		}

		for (nframes = 0; nframes < 16 &&
		    !IFQ_DRV_IS_EMPTY(&ifp->if_snd); nframes++) {
			IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
			if (m == NULL)
				break;
			usbd_xfer_set_frame_offset(xfer, nframes * MCLBYTES,
			    nframes);
			pos = 0;
			pc = usbd_xfer_get_frame(xfer, nframes);
			if (AXE_IS_178_FAMILY(sc)) {
				hdr.len = htole16(m->m_pkthdr.len);
				hdr.ilen = ~hdr.len;
				/*
				 * If upper stack computed checksum, driver
				 * should tell controller not to insert
				 * computed checksum for checksum offloading
				 * enabled controller.
				 */
				if (ifp->if_capabilities & IFCAP_TXCSUM) {
					if ((m->m_pkthdr.csum_flags &
					    AXE_CSUM_FEATURES) != 0)
						hdr.len |= htole16(
						    AXE_TX_CSUM_PSEUDO_HDR);
					else
						hdr.len |= htole16(
						    AXE_TX_CSUM_DIS);
				}
				usbd_copy_in(pc, pos, &hdr, sizeof(hdr));
				pos += sizeof(hdr);
				usbd_m_copy_in(pc, pos, m, 0, m->m_pkthdr.len);
				pos += m->m_pkthdr.len;
				if ((pos % 512) == 0) {
					hdr.len = 0;
					hdr.ilen = 0xffff;
					usbd_copy_in(pc, pos, &hdr,
					    sizeof(hdr));
					pos += sizeof(hdr);
				}
			} else {
				usbd_m_copy_in(pc, pos, m, 0, m->m_pkthdr.len);
				pos += m->m_pkthdr.len;
			}

			/*
			 * XXX
			 * Update TX packet counter here. This is not
			 * correct way but it seems that there is no way
			 * to know how many packets are sent at the end
			 * of transfer because controller combines
			 * multiple writes into single one if there is
			 * room in TX buffer of controller.
			 */
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

			/*
			 * if there's a BPF listener, bounce a copy
			 * of this frame to him:
			 */
			BPF_MTAP(ifp, m);

			m_freem(m);

			/* Set frame length. */
			usbd_xfer_set_frame_len(xfer, nframes, pos);
		}
		if (nframes != 0) {
			usbd_xfer_set_frames(xfer, nframes);
			usbd_transfer_submit(xfer);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
		}
		return;
		/* NOTREACHED */
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