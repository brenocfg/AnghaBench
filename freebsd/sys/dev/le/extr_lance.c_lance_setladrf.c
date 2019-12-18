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
typedef  int uint16_t ;
struct lance_softc {int sc_flags; struct ifnet* sc_ifp; } ;
struct lance_hash_maddr_ctx {int* member_1; struct lance_softc* member_0; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int LE_ALLMULTI ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct lance_hash_maddr_ctx*) ; 
 int /*<<< orphan*/  lance_hash_maddr ; 

void
lance_setladrf(struct lance_softc *sc, uint16_t *af)
{
	struct ifnet *ifp = sc->sc_ifp;
	struct lance_hash_maddr_ctx ctx = { sc, af };

	/*
	 * Set up multicast address filter by passing all multicast addresses
	 * through a crc generator, and then using the high order 6 bits as an
	 * index into the 64 bit logical address filter.  The high order bit
	 * selects the word, while the rest of the bits select the bit within
	 * the word.
	 */

	if (ifp->if_flags & IFF_PROMISC || sc->sc_flags & LE_ALLMULTI) {
		af[0] = af[1] = af[2] = af[3] = 0xffff;
		return;
	}

	af[0] = af[1] = af[2] = af[3] = 0x0000;
	if_foreach_llmaddr(ifp, lance_hash_maddr, &ctx);
}