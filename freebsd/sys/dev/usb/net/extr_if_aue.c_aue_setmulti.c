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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct usb_ether {int dummy; } ;
struct ifnet {int if_flags; } ;
struct aue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_CLRBIT (struct aue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUE_CTL0 ; 
 int /*<<< orphan*/  AUE_CTL0_ALLMULTI ; 
 int /*<<< orphan*/  AUE_LOCK_ASSERT (struct aue_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ AUE_MAR0 ; 
 int /*<<< orphan*/  AUE_SETBIT (struct aue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  aue_csr_write_1 (struct aue_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aue_hash_maddr ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct aue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
aue_setmulti(struct usb_ether *ue)
{
	struct aue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);
	uint32_t i;
	uint8_t hashtbl[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	AUE_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_flags & IFF_ALLMULTI || ifp->if_flags & IFF_PROMISC) {
		AUE_SETBIT(sc, AUE_CTL0, AUE_CTL0_ALLMULTI);
		return;
	}

	AUE_CLRBIT(sc, AUE_CTL0, AUE_CTL0_ALLMULTI);

	/* now program new ones */
	if_foreach_llmaddr(ifp, aue_hash_maddr, hashtbl);

	/* write the hashtable */
	for (i = 0; i != 8; i++)
		aue_csr_write_1(sc, AUE_MAR0 + i, hashtbl[i]);
}