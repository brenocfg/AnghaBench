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
typedef  int /*<<< orphan*/  tx_cmd_b ;
typedef  int /*<<< orphan*/  tx_cmd_a ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct muge_softc {int sc_flags; int /*<<< orphan*/  sc_ue; } ;
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
 int MUGE_FLAG_LINK ; 
 int TX_CMD_A_FCS_ ; 
 int TX_CMD_A_LEN_MASK_ ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int htole32 (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*,...) ; 
 int /*<<< orphan*/  muge_err_printf (struct muge_softc*,char*,int /*<<< orphan*/ ) ; 
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
 struct muge_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
muge_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct muge_softc *sc = usbd_xfer_softc(xfer);
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	struct usb_page_cache *pc;
	struct mbuf *m;
	int nframes;
	uint32_t frm_len = 0, tx_cmd_a = 0, tx_cmd_b = 0;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		muge_dbg_printf(sc,
		    "USB TRANSFER status: USB_ST_TRANSFERRED\n");
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		/* FALLTHROUGH */
	case USB_ST_SETUP:
		muge_dbg_printf(sc, "USB TRANSFER status: USB_ST_SETUP\n");
tr_setup:
		if ((sc->sc_flags & MUGE_FLAG_LINK) == 0 ||
			(ifp->if_drv_flags & IFF_DRV_OACTIVE) != 0) {
			muge_dbg_printf(sc,
			    "sc->sc_flags & MUGE_FLAG_LINK: %d\n",
			    (sc->sc_flags & MUGE_FLAG_LINK));
			muge_dbg_printf(sc,
			    "ifp->if_drv_flags & IFF_DRV_OACTIVE: %d\n",
			    (ifp->if_drv_flags & IFF_DRV_OACTIVE));
			muge_dbg_printf(sc,
			    "USB TRANSFER not sending: no link or controller is busy \n");
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
			frm_len = 0;
			pc = usbd_xfer_get_frame(xfer, nframes);

			/*
			 * Each frame is prefixed with two 32-bit values
			 * describing the length of the packet and buffer.
			 */
			tx_cmd_a = (m->m_pkthdr.len & TX_CMD_A_LEN_MASK_) |
			     TX_CMD_A_FCS_;
			tx_cmd_a = htole32(tx_cmd_a);
			usbd_copy_in(pc, 0, &tx_cmd_a, sizeof(tx_cmd_a));

			tx_cmd_b = 0;

			/* TCP LSO Support will probably be implemented here. */
			tx_cmd_b = htole32(tx_cmd_b);
			usbd_copy_in(pc, 4, &tx_cmd_b, sizeof(tx_cmd_b));

			frm_len += 8;

			/* Next copy in the actual packet */
			usbd_m_copy_in(pc, frm_len, m, 0, m->m_pkthdr.len);
			frm_len += m->m_pkthdr.len;

			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

			/*
			 * If there's a BPF listener, bounce a copy of this
			 * frame to it.
			 */
			BPF_MTAP(ifp, m);
			m_freem(m);

			/* Set frame length. */
			usbd_xfer_set_frame_len(xfer, nframes, frm_len);
		}

		muge_dbg_printf(sc, "USB TRANSFER nframes: %d\n", nframes);
		if (nframes != 0) {
			muge_dbg_printf(sc, "USB TRANSFER submit attempt\n");
			usbd_xfer_set_frames(xfer, nframes);
			usbd_transfer_submit(xfer);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
		}
		return;

	default:
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

		if (error != USB_ERR_CANCELLED) {
			muge_err_printf(sc,
			    "usb error on tx: %s\n", usbd_errstr(error));
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}