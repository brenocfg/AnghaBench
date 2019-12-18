#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_1__ hip; } ;
struct usie_softc {TYPE_3__ sc_txd; struct ifnet* sc_ifp; } ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_5__ {int len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ETHER_CRC_LEN ; 
 int ETHER_HDR_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  htobe16 (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct usie_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
usie_if_tx_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct usie_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	struct ifnet *ifp = sc->sc_ifp;
	struct mbuf *m;
	uint16_t size;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "transfer complete\n");
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		/* fall though */
	case USB_ST_SETUP:
tr_setup:

		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;

		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;

		if (m->m_pkthdr.len > (int)(MCLBYTES - ETHER_HDR_LEN +
		    ETHER_CRC_LEN - sizeof(sc->sc_txd))) {
			DPRINTF("packet len is too big: %d\n",
			    m->m_pkthdr.len);
			break;
		}
		pc = usbd_xfer_get_frame(xfer, 0);

		sc->sc_txd.hip.len = htobe16(m->m_pkthdr.len +
		    ETHER_HDR_LEN + ETHER_CRC_LEN);
		size = sizeof(sc->sc_txd);

		usbd_copy_in(pc, 0, &sc->sc_txd, size);
		usbd_m_copy_in(pc, size, m, 0, m->m_pkthdr.len);
		usbd_xfer_set_frame_len(xfer, 0, m->m_pkthdr.len +
		    size + ETHER_CRC_LEN);

		BPF_MTAP(ifp, m);

		m_freem(m);

		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		DPRINTF("USB transfer error, %s\n",
		    usbd_errstr(error));
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			goto tr_setup;
		}
		break;
	}
}