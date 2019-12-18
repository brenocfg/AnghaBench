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
typedef  int uint8_t ;
struct usb_ether {int dummy; } ;
struct mos_softc {int* mos_ipgs; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MOS_CTL ; 
 int MOS_CTL_BS_ENB ; 
 int MOS_CTL_RX_ENB ; 
 int MOS_CTL_SLEEP ; 
 int MOS_CTL_TX_ENB ; 
 int /*<<< orphan*/  MOS_IPG0 ; 
 int /*<<< orphan*/  MOS_IPG1 ; 
 int /*<<< orphan*/  MOS_LOCK_ASSERT (struct mos_softc*,int /*<<< orphan*/ ) ; 
 void* mos_reg_read_1 (struct mos_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_reg_write_1 (struct mos_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mos_reset (struct mos_softc*) ; 
 int /*<<< orphan*/  mos_setmulti (struct usb_ether*) ; 
 int /*<<< orphan*/  mos_setpromisc (struct usb_ether*) ; 
 int /*<<< orphan*/  mos_start (struct usb_ether*) ; 
 int /*<<< orphan*/  mos_writemac (struct mos_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct mos_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
mos_init(struct usb_ether *ue)
{
	struct mos_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);
	uint8_t rxmode;

	MOS_LOCK_ASSERT(sc, MA_OWNED);

	/* Cancel pending I/O and free all RX/TX buffers. */
	mos_reset(sc);

	/* Write MAC address */
	mos_writemac(sc, IF_LLADDR(ifp));

	/* Read and set transmitter IPG values */
	sc->mos_ipgs[0] = mos_reg_read_1(sc, MOS_IPG0);
	sc->mos_ipgs[1] = mos_reg_read_1(sc, MOS_IPG1);
	mos_reg_write_1(sc, MOS_IPG0, sc->mos_ipgs[0]);
	mos_reg_write_1(sc, MOS_IPG1, sc->mos_ipgs[1]);

	/*
	 * Enable receiver and transmitter, bridge controls speed/duplex
	 * mode
	 */
	rxmode = mos_reg_read_1(sc, MOS_CTL);
	rxmode |= MOS_CTL_RX_ENB | MOS_CTL_TX_ENB | MOS_CTL_BS_ENB;
	rxmode &= ~(MOS_CTL_SLEEP);

	mos_setpromisc(ue);

	/* XXX: broadcast mode? */
	mos_reg_write_1(sc, MOS_CTL, rxmode);

	/* Load the multicast filter. */
	mos_setmulti(ue);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	mos_start(ue);
}