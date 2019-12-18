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
struct atse_softc {int* atse_eth_addr; } ;

/* Variables and functions */
 int ATSE_ETH_ADDR_DEF ; 
 int ATSE_ETH_ADDR_SUPP1 ; 
 int ATSE_ETH_ADDR_SUPP2 ; 
 int ATSE_ETH_ADDR_SUPP3 ; 
 int ATSE_ETH_ADDR_SUPP4 ; 
 int /*<<< orphan*/  BASE_CFG_MAC_0 ; 
 int /*<<< orphan*/  BASE_CFG_MAC_1 ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct atse_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_0_0 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_0_1 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_1_0 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_1_1 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_2_0 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_2_1 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_3_0 ; 
 int /*<<< orphan*/  SUPPL_ADDR_SMAC_3_1 ; 

__attribute__((used)) static int
atse_set_eth_address(struct atse_softc *sc, int n)
{
	uint32_t v0, v1;

	v0 = (sc->atse_eth_addr[3] << 24) | (sc->atse_eth_addr[2] << 16) |
	    (sc->atse_eth_addr[1] << 8) | sc->atse_eth_addr[0];
	v1 = (sc->atse_eth_addr[5] << 8) | sc->atse_eth_addr[4];

	if (n & ATSE_ETH_ADDR_DEF) {
		CSR_WRITE_4(sc, BASE_CFG_MAC_0, v0);
		CSR_WRITE_4(sc, BASE_CFG_MAC_1, v1);
	}
	if (n & ATSE_ETH_ADDR_SUPP1) {
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_0_0, v0);
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_0_1, v1);
	}
	if (n & ATSE_ETH_ADDR_SUPP2) {
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_1_0, v0);
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_1_1, v1);
	}
	if (n & ATSE_ETH_ADDR_SUPP3) {
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_2_0, v0);
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_2_1, v1);
	}
	if (n & ATSE_ETH_ADDR_SUPP4) {
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_3_0, v0);
		CSR_WRITE_4(sc, SUPPL_ADDR_SMAC_3_1, v1);
	}

	return (0);
}