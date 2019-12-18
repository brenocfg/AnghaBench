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
struct nf10bmac_softc {int* nf10bmac_eth_addr; scalar_t__ nf10bmac_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nf10bmac_reset(struct nf10bmac_softc *sc)
{

	/*
	 * If we do not have an ether address set, initialize to the same
	 * OUI as NetFPGA-10G Linux driver does (which luckily seems
	 * unallocated).  We just change the NIC specific part from
	 * the slightly long "\0NF10C0" to "\0NFBSD".
	 * Oh and we keep the way of setting it from a string as they do.
	 * It's an amazing way to hide it.
	 * XXX-BZ If NetFPGA gets their own OUI we should fix this.
	 */
	if (sc->nf10bmac_eth_addr[0] == 0x00 &&
	    sc->nf10bmac_eth_addr[1] == 0x00 &&
	    sc->nf10bmac_eth_addr[2] == 0x00 &&
	    sc->nf10bmac_eth_addr[3] == 0x00 &&
	    sc->nf10bmac_eth_addr[4] == 0x00 &&
	    sc->nf10bmac_eth_addr[5] == 0x00) {
		memcpy(&sc->nf10bmac_eth_addr, "\0NFBSD", ETHER_ADDR_LEN);
		sc->nf10bmac_eth_addr[5] += sc->nf10bmac_unit;
	}

	return (0);
}