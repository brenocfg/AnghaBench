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
typedef  int u_int8_t ;
struct xl_softc {struct ifnet* xl_ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_1 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int XL_CMD_RX_SET_FILT ; 
 int /*<<< orphan*/  XL_COMMAND ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int XL_RXFILTER_ALLFRAMES ; 
 int XL_RXFILTER_ALLMULTI ; 
 int XL_RXFILTER_BROADCAST ; 
 int XL_RXFILTER_INDIVIDUAL ; 
 int /*<<< orphan*/  XL_SEL_WIN (int) ; 
 int /*<<< orphan*/  XL_W5_RX_FILTER ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xl_check_maddr_90x ; 

__attribute__((used)) static void
xl_rxfilter_90x(struct xl_softc *sc)
{
	struct ifnet		*ifp;
	u_int8_t		rxfilt;

	XL_LOCK_ASSERT(sc);

	ifp = sc->xl_ifp;

	XL_SEL_WIN(5);
	rxfilt = CSR_READ_1(sc, XL_W5_RX_FILTER);
	rxfilt &= ~(XL_RXFILTER_ALLFRAMES | XL_RXFILTER_ALLMULTI |
	    XL_RXFILTER_BROADCAST | XL_RXFILTER_INDIVIDUAL);

	/* Set the individual bit to receive frames for this host only. */
	rxfilt |= XL_RXFILTER_INDIVIDUAL;
	/* Set capture broadcast bit to capture broadcast frames. */
	if (ifp->if_flags & IFF_BROADCAST)
		rxfilt |= XL_RXFILTER_BROADCAST;

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->if_flags & (IFF_PROMISC | IFF_ALLMULTI)) {
		if (ifp->if_flags & IFF_PROMISC)
			rxfilt |= XL_RXFILTER_ALLFRAMES;
		if (ifp->if_flags & IFF_ALLMULTI)
			rxfilt |= XL_RXFILTER_ALLMULTI;
	} else
		if_foreach_llmaddr(sc->xl_ifp, xl_check_maddr_90x, &rxfilt);

	CSR_WRITE_2(sc, XL_COMMAND, rxfilt | XL_CMD_RX_SET_FILT);
	XL_SEL_WIN(7);
}