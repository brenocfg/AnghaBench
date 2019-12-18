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
struct gem_softc {int sc_mac_rxcfg; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  GEM_BANK1_BARRIER (struct gem_softc*,int,int,int) ; 
 int /*<<< orphan*/  GEM_BANK1_BITWAIT (struct gem_softc*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int,int) ; 
 int /*<<< orphan*/  GEM_LOCK_ASSERT (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int GEM_MAC_HASH0 ; 
 int GEM_MAC_HASH1 ; 
 int GEM_MAC_RX_CONFIG ; 
 int GEM_MAC_RX_ENABLE ; 
 int GEM_MAC_RX_HASH_FILTER ; 
 int GEM_MAC_RX_PROMISCUOUS ; 
 int GEM_MAC_RX_PROMISC_GRP ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gem_hash_maddr ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gem_setladrf(struct gem_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	int i;
	uint32_t hash[16];
	uint32_t v;

	GEM_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Turn off the RX MAC and the hash filter as required by the Sun GEM
	 * programming restrictions.
	 */
	v = sc->sc_mac_rxcfg & ~GEM_MAC_RX_HASH_FILTER;
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_CONFIG, v);
	GEM_BANK1_BARRIER(sc, GEM_MAC_RX_CONFIG, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!GEM_BANK1_BITWAIT(sc, GEM_MAC_RX_CONFIG, GEM_MAC_RX_HASH_FILTER |
	    GEM_MAC_RX_ENABLE, 0))
		device_printf(sc->sc_dev,
		    "cannot disable RX MAC or hash filter\n");

	v &= ~(GEM_MAC_RX_PROMISCUOUS | GEM_MAC_RX_PROMISC_GRP);
	if ((ifp->if_flags & IFF_PROMISC) != 0) {
		v |= GEM_MAC_RX_PROMISCUOUS;
		goto chipit;
	}
	if ((ifp->if_flags & IFF_ALLMULTI) != 0) {
		v |= GEM_MAC_RX_PROMISC_GRP;
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
	if_foreach_llmaddr(ifp, gem_hash_maddr, hash);

	v |= GEM_MAC_RX_HASH_FILTER;

	/* Now load the hash table into the chip (if we are using it). */
	for (i = 0; i < 16; i++)
		GEM_BANK1_WRITE_4(sc,
		    GEM_MAC_HASH0 + i * (GEM_MAC_HASH1 - GEM_MAC_HASH0),
		    hash[i]);

 chipit:
	sc->sc_mac_rxcfg = v;
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_CONFIG, v | GEM_MAC_RX_ENABLE);
}