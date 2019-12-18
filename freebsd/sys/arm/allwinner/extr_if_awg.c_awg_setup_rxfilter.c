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
typedef  int uint32_t ;
struct awg_softc {int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_ASSERT_LOCKED (struct awg_softc*) ; 
 int DIS_ADDR_FILTER ; 
 int /*<<< orphan*/  EMAC_ADDR_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_ADDR_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_RX_FRM_FLT ; 
 int /*<<< orphan*/  EMAC_RX_HASH_0 ; 
 int /*<<< orphan*/  EMAC_RX_HASH_1 ; 
 int HASH_MULTICAST ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int* IF_LLADDR (int /*<<< orphan*/ ) ; 
 int RX_ALL_MULTICAST ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  awg_hash_maddr ; 
 scalar_t__ if_foreach_llmaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
awg_setup_rxfilter(struct awg_softc *sc)
{
	uint32_t val, hash[2], machi, maclo;
	uint8_t *eaddr;
	if_t ifp;

	AWG_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	val = 0;
	hash[0] = hash[1] = 0;

	if (if_getflags(ifp) & IFF_PROMISC)
		val |= DIS_ADDR_FILTER;
	else if (if_getflags(ifp) & IFF_ALLMULTI) {
		val |= RX_ALL_MULTICAST;
		hash[0] = hash[1] = ~0;
	} else if (if_foreach_llmaddr(ifp, awg_hash_maddr, hash) > 0)
		val |= HASH_MULTICAST;

	/* Write our unicast address */
	eaddr = IF_LLADDR(ifp);
	machi = (eaddr[5] << 8) | eaddr[4];
	maclo = (eaddr[3] << 24) | (eaddr[2] << 16) | (eaddr[1] << 8) |
	   (eaddr[0] << 0);
	WR4(sc, EMAC_ADDR_HIGH(0), machi);
	WR4(sc, EMAC_ADDR_LOW(0), maclo);

	/* Multicast hash filters */
	WR4(sc, EMAC_RX_HASH_0, hash[1]);
	WR4(sc, EMAC_RX_HASH_1, hash[0]);

	/* RX frame filter config */
	WR4(sc, EMAC_RX_FRM_FLT, val);
}