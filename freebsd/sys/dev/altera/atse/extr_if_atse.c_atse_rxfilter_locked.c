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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ifnet {int if_flags; } ;
struct atse_softc {struct ifnet* atse_ifp; } ;

/* Variables and functions */
 scalar_t__ BASE_CFG_COMMAND_CONFIG ; 
 int BASE_CFG_COMMAND_CONFIG_MHASH_SEL ; 
 int BASE_CFG_COMMAND_CONFIG_PROMIS_EN ; 
 int CSR_READ_4 (struct atse_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct atse_softc*,scalar_t__,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MHASH_LEN ; 
 scalar_t__ MHASH_START ; 
 int /*<<< orphan*/  atse_hash_maddr ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
atse_rxfilter_locked(struct atse_softc *sc)
{
	struct ifnet *ifp;
	uint32_t val4;
	int i;

	/* XXX-BZ can we find out if we have the MHASH synthesized? */
	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
	/* For simplicity always hash full 48 bits of addresses. */
	if ((val4 & BASE_CFG_COMMAND_CONFIG_MHASH_SEL) != 0)
		val4 &= ~BASE_CFG_COMMAND_CONFIG_MHASH_SEL;

	ifp = sc->atse_ifp;
	if (ifp->if_flags & IFF_PROMISC) {
		val4 |= BASE_CFG_COMMAND_CONFIG_PROMIS_EN;
	} else {
		val4 &= ~BASE_CFG_COMMAND_CONFIG_PROMIS_EN;
	}

	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);

	if (ifp->if_flags & IFF_ALLMULTI) {
		/* Accept all multicast addresses. */
		for (i = 0; i <= MHASH_LEN; i++)
			CSR_WRITE_4(sc, MHASH_START + i, 0x1);
	} else {
		/*
		 * Can hold MHASH_LEN entries.
		 * XXX-BZ bitstring.h would be more general.
		 */
		uint64_t h;

		/*
		 * Re-build and re-program hash table.  First build the
		 * bit-field "yes" or "no" for each slot per address, then
		 * do all the programming afterwards.
		 */
		h = 0;
		(void)if_foreach_llmaddr(ifp, atse_hash_maddr, &h);
		for (i = 0; i <= MHASH_LEN; i++) {
			CSR_WRITE_4(sc, MHASH_START + i,
			    (h & (1 << i)) ? 0x01 : 0x00);
		}
	}

	return (0);
}