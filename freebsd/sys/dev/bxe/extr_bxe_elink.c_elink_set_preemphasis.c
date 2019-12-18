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
typedef  scalar_t__ uint16_t ;
struct elink_phy {int /*<<< orphan*/ * tx_preemphasis; int /*<<< orphan*/ * rx_preemphasis; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MDIO_REG_BANK_RX0 ; 
 scalar_t__ MDIO_REG_BANK_RX1 ; 
 scalar_t__ MDIO_REG_BANK_RX3 ; 
 scalar_t__ MDIO_REG_BANK_TX0 ; 
 scalar_t__ MDIO_REG_BANK_TX1 ; 
 scalar_t__ MDIO_REG_BANK_TX3 ; 
 int /*<<< orphan*/  MDIO_RX0_RX_EQ_BOOST ; 
 int /*<<< orphan*/  MDIO_TX0_TX_DRIVER ; 

__attribute__((used)) static void elink_set_preemphasis(struct elink_phy *phy,
				  struct elink_params *params)
{

	uint16_t bank, i = 0;
	struct bxe_softc *sc = params->sc;

	for (bank = MDIO_REG_BANK_RX0, i = 0; bank <= MDIO_REG_BANK_RX3;
	      bank += (MDIO_REG_BANK_RX1-MDIO_REG_BANK_RX0), i++) {
			CL22_WR_OVER_CL45(sc, phy,
					  bank,
					  MDIO_RX0_RX_EQ_BOOST,
					  phy->rx_preemphasis[i]);
	}

	for (bank = MDIO_REG_BANK_TX0, i = 0; bank <= MDIO_REG_BANK_TX3;
		      bank += (MDIO_REG_BANK_TX1 - MDIO_REG_BANK_TX0), i++) {
			CL22_WR_OVER_CL45(sc, phy,
					  bank,
					  MDIO_TX0_TX_DRIVER,
					  phy->tx_preemphasis[i]);
	}
}