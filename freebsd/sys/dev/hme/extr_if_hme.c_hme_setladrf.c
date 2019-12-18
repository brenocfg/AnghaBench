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
typedef  int u_int32_t ;
struct ifnet {int if_flags; } ;
struct hme_softc {int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_LOCK_ASSERT (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MACI_HASHTAB0 ; 
 int /*<<< orphan*/  HME_MACI_HASHTAB1 ; 
 int /*<<< orphan*/  HME_MACI_HASHTAB2 ; 
 int /*<<< orphan*/  HME_MACI_HASHTAB3 ; 
 int /*<<< orphan*/  HME_MACI_RXCFG ; 
 int HME_MAC_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int HME_MAC_RXCFG_ENABLE ; 
 int HME_MAC_RXCFG_HENABLE ; 
 int HME_MAC_RXCFG_ME ; 
 int HME_MAC_RXCFG_PGRP ; 
 int HME_MAC_RXCFG_PMISC ; 
 int /*<<< orphan*/  HME_MAC_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hme_hash_maddr ; 
 int /*<<< orphan*/  hme_mac_bitflip (struct hme_softc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int**) ; 

__attribute__((used)) static void
hme_setladrf(struct hme_softc *sc, int reenable)
{
	struct ifnet *ifp = sc->sc_ifp;
	u_int32_t hash[4];
	u_int32_t macc;

	HME_LOCK_ASSERT(sc, MA_OWNED);
	/* Clear the hash table. */
	hash[3] = hash[2] = hash[1] = hash[0] = 0;

	/* Get the current RX configuration. */
	macc = HME_MAC_READ_4(sc, HME_MACI_RXCFG);

	/*
	 * Turn off promiscuous mode, promiscuous group mode (all multicast),
	 * and hash filter.  Depending on the case, the right bit will be
	 * enabled.
	 */
	macc &= ~(HME_MAC_RXCFG_PGRP | HME_MAC_RXCFG_PMISC);

	/*
	 * Disable the receiver while changing it's state as the documentation
	 * mandates.
	 * We then must wait until the bit clears in the register. This should
	 * take at most 3.5ms.
	 */
	if (!hme_mac_bitflip(sc, HME_MACI_RXCFG, macc,
	    HME_MAC_RXCFG_ENABLE, 0))
		device_printf(sc->sc_dev, "cannot disable RX MAC\n");
	/* Disable the hash filter before writing to the filter registers. */
	if (!hme_mac_bitflip(sc, HME_MACI_RXCFG, macc,
	    HME_MAC_RXCFG_HENABLE, 0))
		device_printf(sc->sc_dev, "cannot disable hash filter\n");

	/* Make the RX MAC really SIMPLEX. */
	macc |= HME_MAC_RXCFG_ME;
	if (reenable)
		macc |= HME_MAC_RXCFG_ENABLE;
	else
		macc &= ~HME_MAC_RXCFG_ENABLE;

	if ((ifp->if_flags & IFF_PROMISC) != 0) {
		macc |= HME_MAC_RXCFG_PMISC;
		goto chipit;
	}
	if ((ifp->if_flags & IFF_ALLMULTI) != 0) {
		macc |= HME_MAC_RXCFG_PGRP;
		goto chipit;
	}

	macc |= HME_MAC_RXCFG_HENABLE;

	/*
	 * Set up multicast address filter by passing all multicast addresses
	 * through a crc generator, and then using the high order 6 bits as an
	 * index into the 64 bit logical address filter.  The high order bit
	 * selects the word, while the rest of the bits select the bit within
	 * the word.
	 */
	if_foreach_llmaddr(ifp, hme_hash_maddr, &hash);

chipit:
	/* Now load the hash table into the chip */
	HME_MAC_WRITE_4(sc, HME_MACI_HASHTAB0, hash[0]);
	HME_MAC_WRITE_4(sc, HME_MACI_HASHTAB1, hash[1]);
	HME_MAC_WRITE_4(sc, HME_MACI_HASHTAB2, hash[2]);
	HME_MAC_WRITE_4(sc, HME_MACI_HASHTAB3, hash[3]);
	if (!hme_mac_bitflip(sc, HME_MACI_RXCFG, macc, 0,
	    macc & (HME_MAC_RXCFG_ENABLE | HME_MAC_RXCFG_HENABLE |
	    HME_MAC_RXCFG_ME)))
		device_printf(sc->sc_dev, "cannot configure RX MAC\n");
}