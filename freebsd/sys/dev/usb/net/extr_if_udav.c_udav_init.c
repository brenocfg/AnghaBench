#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_ether {struct udav_softc* ue_sc; } ;
struct udav_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t UDAV_BULK_DT_WR ; 
 int /*<<< orphan*/  UDAV_CLRBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDAV_GPCR ; 
 int UDAV_GPCR_GEP_CNTL0 ; 
 int /*<<< orphan*/  UDAV_GPR ; 
 int UDAV_GPR_GEPIO0 ; 
 int /*<<< orphan*/  UDAV_LOCK_ASSERT (struct udav_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDAV_NCR ; 
 int UDAV_NCR_LBK0 ; 
 int UDAV_NCR_LBK1 ; 
 int /*<<< orphan*/  UDAV_PAR ; 
 int /*<<< orphan*/  UDAV_RCR ; 
 int UDAV_RCR_DIS_CRC ; 
 int UDAV_RCR_DIS_LONG ; 
 int UDAV_RCR_RXEN ; 
 int /*<<< orphan*/  UDAV_SETBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udav_csr_write (struct udav_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udav_setpromisc (struct usb_ether*) ; 
 int /*<<< orphan*/  udav_start (struct usb_ether*) ; 
 int /*<<< orphan*/  udav_stop (struct usb_ether*) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
udav_init(struct usb_ether *ue)
{
	struct udav_softc *sc = ue->ue_sc;
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);

	UDAV_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Cancel pending I/O
	 */
	udav_stop(ue);

	/* set MAC address */
	udav_csr_write(sc, UDAV_PAR, IF_LLADDR(ifp), ETHER_ADDR_LEN);

	/* initialize network control register */

	/* disable loopback  */
	UDAV_CLRBIT(sc, UDAV_NCR, UDAV_NCR_LBK0 | UDAV_NCR_LBK1);

	/* Initialize RX control register */
	UDAV_SETBIT(sc, UDAV_RCR, UDAV_RCR_DIS_LONG | UDAV_RCR_DIS_CRC);

	/* load multicast filter and update promiscious mode bit */
	udav_setpromisc(ue);

	/* enable RX */
	UDAV_SETBIT(sc, UDAV_RCR, UDAV_RCR_RXEN);

	/* clear POWER_DOWN state of internal PHY */
	UDAV_SETBIT(sc, UDAV_GPCR, UDAV_GPCR_GEP_CNTL0);
	UDAV_CLRBIT(sc, UDAV_GPR, UDAV_GPR_GEPIO0);

	usbd_xfer_set_stall(sc->sc_xfer[UDAV_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	udav_start(ue);
}