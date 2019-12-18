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
struct usb_ether {struct udav_softc* ue_sc; } ;
struct udav_softc {int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  hashtbl ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UDAV_CLRBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDAV_LOCK_ASSERT (struct udav_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDAV_MAR ; 
 int /*<<< orphan*/  UDAV_RCR ; 
 int UDAV_RCR_ALL ; 
 int UDAV_RCR_PRMSC ; 
 int /*<<< orphan*/  UDAV_SETBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  udav_csr_write (struct udav_softc*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  udav_hash_maddr ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
udav_setmulti(struct usb_ether *ue)
{
	struct udav_softc *sc = ue->ue_sc;
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	uint8_t hashtbl[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	UDAV_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_flags & IFF_ALLMULTI || ifp->if_flags & IFF_PROMISC) {
		UDAV_SETBIT(sc, UDAV_RCR, UDAV_RCR_ALL|UDAV_RCR_PRMSC);
		return;
	}

	/* first, zot all the existing hash bits */
	memset(hashtbl, 0x00, sizeof(hashtbl));
	hashtbl[7] |= 0x80;	/* broadcast address */
	udav_csr_write(sc, UDAV_MAR, hashtbl, sizeof(hashtbl));

	/* now program new ones */
	if_foreach_llmaddr(ifp, udav_hash_maddr, hashtbl);

	/* disable all multicast */
	UDAV_CLRBIT(sc, UDAV_RCR, UDAV_RCR_ALL);

	/* write hash value to the register */
	udav_csr_write(sc, UDAV_MAR, hashtbl, sizeof(hashtbl));
}