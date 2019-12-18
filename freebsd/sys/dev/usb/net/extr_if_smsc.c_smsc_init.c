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
struct usb_ether {int dummy; } ;
struct smsc_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int if_drv_flags; int if_capabilities; int if_capenable; scalar_t__ if_hwassist; } ;

/* Variables and functions */
 int IFCAP_RXCSUM ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t SMSC_BULK_DT_WR ; 
 int /*<<< orphan*/  SMSC_LOCK_ASSERT (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_dbg_printf (struct smsc_softc*,char*) ; 
 int /*<<< orphan*/  smsc_ifmedia_upd (struct ifnet*) ; 
 int /*<<< orphan*/  smsc_reset (struct smsc_softc*) ; 
 int /*<<< orphan*/  smsc_sethwcsum (struct smsc_softc*) ; 
 scalar_t__ smsc_setmacaddress (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_setmulti (struct usb_ether*) ; 
 int /*<<< orphan*/  smsc_start (struct usb_ether*) ; 
 int /*<<< orphan*/  smsc_stop (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct smsc_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smsc_init(struct usb_ether *ue)
{
	struct smsc_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	SMSC_LOCK_ASSERT(sc, MA_OWNED);

	if (smsc_setmacaddress(sc, IF_LLADDR(ifp)))
		smsc_dbg_printf(sc, "setting MAC address failed\n");

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/* Cancel pending I/O */
	smsc_stop(ue);

#if __FreeBSD_version <= 1000000
	/* On earlier versions this was the first place we could tell the system
	 * that we supported h/w csuming, however this is only called after the
	 * the interface has been brought up - not ideal.  
	 */
	if (!(ifp->if_capabilities & IFCAP_RXCSUM)) {
		ifp->if_capabilities |= IFCAP_RXCSUM;
		ifp->if_capenable |= IFCAP_RXCSUM;
		ifp->if_hwassist = 0;
	}
	
	/* TX checksuming is disabled for now
	ifp->if_capabilities |= IFCAP_TXCSUM;
	ifp->if_capenable |= IFCAP_TXCSUM;
	ifp->if_hwassist = CSUM_TCP | CSUM_UDP;
	*/
#endif

	/* Reset the ethernet interface. */
	smsc_reset(sc);

	/* Load the multicast filter. */
	smsc_setmulti(ue);

	/* TCP/UDP checksum offload engines. */
	smsc_sethwcsum(sc);

	usbd_xfer_set_stall(sc->sc_xfer[SMSC_BULK_DT_WR]);

	/* Indicate we are up and running. */
	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	/* Switch to selected media. */
	smsc_ifmedia_upd(ifp);
	smsc_start(ue);
}