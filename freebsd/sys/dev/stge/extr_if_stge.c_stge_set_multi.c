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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct stge_softc {struct ifnet* sc_ifp; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  mchash ;

/* Variables and functions */
 int CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int RM_ReceiveAllFrames ; 
 int RM_ReceiveMulticast ; 
 int RM_ReceiveMulticastHash ; 
 int /*<<< orphan*/  STGE_HashTable0 ; 
 int /*<<< orphan*/  STGE_HashTable1 ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_ReceiveMode ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stge_hash_maddr ; 

__attribute__((used)) static void
stge_set_multi(struct stge_softc *sc)
{
	struct ifnet *ifp;
	uint32_t mchash[2];
	uint16_t mode;
	int count;

	STGE_LOCK_ASSERT(sc);

	ifp = sc->sc_ifp;

	mode = CSR_READ_2(sc, STGE_ReceiveMode);
	if ((ifp->if_flags & (IFF_PROMISC | IFF_ALLMULTI)) != 0) {
		if ((ifp->if_flags & IFF_PROMISC) != 0)
			mode |= RM_ReceiveAllFrames;
		else if ((ifp->if_flags & IFF_ALLMULTI) != 0)
			mode |= RM_ReceiveMulticast;
		CSR_WRITE_2(sc, STGE_ReceiveMode, mode);
		return;
	}

	/* clear existing filters. */
	CSR_WRITE_4(sc, STGE_HashTable0, 0);
	CSR_WRITE_4(sc, STGE_HashTable1, 0);

	/*
	 * Set up the multicast address filter by passing all multicast
	 * addresses through a CRC generator, and then using the low-order
	 * 6 bits as an index into the 64 bit multicast hash table.  The
	 * high order bits select the register, while the rest of the bits
	 * select the bit within the register.
	 */
	bzero(mchash, sizeof(mchash));
	count = if_foreach_llmaddr(ifp, stge_hash_maddr, mchash);

	mode &= ~(RM_ReceiveMulticast | RM_ReceiveAllFrames);
	if (count > 0)
		mode |= RM_ReceiveMulticastHash;
	else
		mode &= ~RM_ReceiveMulticastHash;

	CSR_WRITE_4(sc, STGE_HashTable0, mchash[0]);
	CSR_WRITE_4(sc, STGE_HashTable1, mchash[1]);
	CSR_WRITE_2(sc, STGE_ReceiveMode, mode);
}