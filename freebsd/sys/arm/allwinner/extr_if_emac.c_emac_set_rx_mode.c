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
typedef  int uint32_t ;
struct ifnet {int if_flags; } ;
struct emac_softc {struct ifnet* emac_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_ASSERT_LOCKED (struct emac_softc*) ; 
 int EMAC_READ_REG (struct emac_softc*,int /*<<< orphan*/ ) ; 
 int EMAC_RX_BCO ; 
 int /*<<< orphan*/  EMAC_RX_CTL ; 
 int EMAC_RX_DAF ; 
 int /*<<< orphan*/  EMAC_RX_HASH0 ; 
 int /*<<< orphan*/  EMAC_RX_HASH1 ; 
 int EMAC_RX_MCO ; 
 int EMAC_RX_MHF ; 
 int EMAC_RX_PA ; 
 int EMAC_RX_UCAD ; 
 int /*<<< orphan*/  EMAC_WRITE_REG (struct emac_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  emac_hash_maddr ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
emac_set_rx_mode(struct emac_softc *sc)
{
	struct ifnet *ifp;
	uint32_t hashes[2];
	uint32_t rcr = 0;

	EMAC_ASSERT_LOCKED(sc);

	ifp = sc->emac_ifp;

	rcr = EMAC_READ_REG(sc, EMAC_RX_CTL);

	/* Unicast packet and DA filtering */
	rcr |= EMAC_RX_UCAD;
	rcr |= EMAC_RX_DAF;

	hashes[0] = 0;
	hashes[1] = 0;
	if (ifp->if_flags & IFF_ALLMULTI) {
		hashes[0] = 0xffffffff;
		hashes[1] = 0xffffffff;
	} else
		if_foreach_llmaddr(ifp, emac_hash_maddr, hashes);
	rcr |= EMAC_RX_MCO;
	rcr |= EMAC_RX_MHF;
	EMAC_WRITE_REG(sc, EMAC_RX_HASH0, hashes[0]);
	EMAC_WRITE_REG(sc, EMAC_RX_HASH1, hashes[1]);

	if (ifp->if_flags & IFF_BROADCAST) {
		rcr |= EMAC_RX_BCO;
		rcr |= EMAC_RX_MCO;
	}

	if (ifp->if_flags & IFF_PROMISC)
		rcr |= EMAC_RX_PA;
	else
		rcr |= EMAC_RX_UCAD;

	EMAC_WRITE_REG(sc, EMAC_RX_CTL, rcr);
}