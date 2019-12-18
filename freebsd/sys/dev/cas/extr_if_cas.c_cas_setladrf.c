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
struct cas_softc {int sc_mac_rxcfg; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CAS_BARRIER (struct cas_softc*,int,int,int) ; 
 int /*<<< orphan*/  CAS_LOCK_ASSERT (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int CAS_MAC_HASH0 ; 
 int CAS_MAC_HASH1 ; 
 int CAS_MAC_RX_CONF ; 
 int CAS_MAC_RX_CONF_EN ; 
 int CAS_MAC_RX_CONF_HFILTER ; 
 int CAS_MAC_RX_CONF_PGRP ; 
 int CAS_MAC_RX_CONF_PROMISC ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cas_bitwait (struct cas_softc*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_hash_maddr ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cas_setladrf(struct cas_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	int i;
	uint32_t hash[16];
	uint32_t v;

	CAS_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Turn off the RX MAC and the hash filter as required by the Sun
	 * Cassini programming restrictions.
	 */
	v = sc->sc_mac_rxcfg & ~(CAS_MAC_RX_CONF_HFILTER |
	    CAS_MAC_RX_CONF_EN);
	CAS_WRITE_4(sc, CAS_MAC_RX_CONF, v);
	CAS_BARRIER(sc, CAS_MAC_RX_CONF, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!cas_bitwait(sc, CAS_MAC_RX_CONF, CAS_MAC_RX_CONF_HFILTER |
	    CAS_MAC_RX_CONF_EN, 0))
		device_printf(sc->sc_dev,
		    "cannot disable RX MAC or hash filter\n");

	v &= ~(CAS_MAC_RX_CONF_PROMISC | CAS_MAC_RX_CONF_PGRP);
	if ((ifp->if_flags & IFF_PROMISC) != 0) {
		v |= CAS_MAC_RX_CONF_PROMISC;
		goto chipit;
	}
	if ((ifp->if_flags & IFF_ALLMULTI) != 0) {
		v |= CAS_MAC_RX_CONF_PGRP;
		goto chipit;
	}

	/*
	 * Set up multicast address filter by passing all multicast
	 * addresses through a crc generator, and then using the high
	 * order 8 bits as an index into the 256 bit logical address
	 * filter.  The high order 4 bits selects the word, while the
	 * other 4 bits select the bit within the word (where bit 0
	 * is the MSB).
	 */

	memset(hash, 0, sizeof(hash));
	if_foreach_llmaddr(ifp, cas_hash_maddr, &hash);

	v |= CAS_MAC_RX_CONF_HFILTER;

	/* Now load the hash table into the chip (if we are using it). */
	for (i = 0; i < 16; i++)
		CAS_WRITE_4(sc,
		    CAS_MAC_HASH0 + i * (CAS_MAC_HASH1 - CAS_MAC_HASH0),
		    hash[i]);

 chipit:
	sc->sc_mac_rxcfg = v;
	CAS_WRITE_4(sc, CAS_MAC_RX_CONF, v | CAS_MAC_RX_CONF_EN);
}