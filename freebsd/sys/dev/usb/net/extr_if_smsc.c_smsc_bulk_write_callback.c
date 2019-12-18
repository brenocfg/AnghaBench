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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  txhdr ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct smsc_softc {int sc_flags; int /*<<< orphan*/  sc_ue; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int MCLBYTES ; 
 int SMSC_FLAG_LINK ; 
 int SMSC_TX_CTRL_0_BUF_SIZE (int) ; 
 int SMSC_TX_CTRL_0_FIRST_SEG ; 
 int SMSC_TX_CTRL_0_LAST_SEG ; 
 int SMSC_TX_CTRL_1_PKT_LENGTH (int) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int htole32 (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  smsc_err_printf (struct smsc_softc*,char*,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int,int*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_offset (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct smsc_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
smsc_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct smsc_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct usb_page_cache *pc;
	struct mbuf *m;
	uint32_t txhdr;
	uint32_t frm_len = 0;
	int nframes;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		/* FALLTHROUGH */

	case USB_ST_SETUP:
tr_setup:
		if ((sc->sc_flags & SMSC_FLAG_LINK) == 0 ||
			(ifp->if_drv_flags & IFF_DRV_OACTIVE) != 0) {
			/* Don't send anything if there is no link or controller is busy. */
			return;
		}

		for (nframes = 0; nframes < 16 &&
		    !IFQ_DRV_IS_EMPTY(&ifp->if_snd); nframes++) {
			IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
			if (m == NULL)
				break;
			usbd_xfer_set_frame_offset(xfer, nframes * MCLBYTES,
			    nframes);
			frm_len = 0;
			pc = usbd_xfer_get_frame(xfer, nframes);

			/* Each frame is prefixed with two 32-bit values describing the
			 * length of the packet and buffer.
			 */
			txhdr = SMSC_TX_CTRL_0_BUF_SIZE(m->m_pkthdr.len) | 
					SMSC_TX_CTRL_0_FIRST_SEG | SMSC_TX_CTRL_0_LAST_SEG;
			txhdr = htole32(txhdr);
			usbd_copy_in(pc, 0, &txhdr, sizeof(txhdr));
			
			txhdr = SMSC_TX_CTRL_1_PKT_LENGTH(m->m_pkthdr.len);
			txhdr = htole32(txhdr);
			usbd_copy_in(pc, 4, &txhdr, sizeof(txhdr));
			
			frm_len += 8;

			/* Next copy in the actual packet */
			usbd_m_copy_in(pc, frm_len, m, 0, m->m_pkthdr.len);
			frm_len += m->m_pkthdr.len;

			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

			/* If there's a BPF listener, bounce a copy of this frame to him */
			BPF_MTAP(ifp, m);

			m_freem(m);

			/* Set frame length. */
			usbd_xfer_set_frame_len(xfer, nframes, frm_len);
		}
		if (nframes != 0) {
			usbd_xfer_set_frames(xfer, nframes);
			usbd_transfer_submit(xfer);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
		}
		return;

	default:
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		
		if (error != USB_ERR_CANCELLED) {
			smsc_err_printf(sc, "usb error on tx: %s\n", usbd_errstr(error));
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}