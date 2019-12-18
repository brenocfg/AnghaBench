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
typedef  int uint16_t ;
struct elink_phy {int addr; scalar_t__ mdio_ctrl; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  ELINK_STATUS_TIMEOUT ; 
 int EMAC_MDIO_COMM_COMMAND_READ_22 ; 
 int EMAC_MDIO_COMM_DATA ; 
 int EMAC_MDIO_COMM_START_BUSY ; 
 int EMAC_MDIO_MODE_CLAUSE_45 ; 
 scalar_t__ EMAC_REG_EMAC_MDIO_COMM ; 
 scalar_t__ EMAC_REG_EMAC_MDIO_MODE ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static elink_status_t elink_cl22_read(struct bxe_softc *sc,
				      struct elink_phy *phy,
				      uint16_t reg, uint16_t *ret_val)
{
	uint32_t val, mode;
	uint16_t i;
	elink_status_t rc = ELINK_STATUS_OK;

	/* Switch to CL22 */
	mode = REG_RD(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE);
	REG_WR(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE,
	       mode & ~EMAC_MDIO_MODE_CLAUSE_45);

	/* Address */
	val = ((phy->addr << 21) | (reg << 16) |
	       EMAC_MDIO_COMM_COMMAND_READ_22 |
	       EMAC_MDIO_COMM_START_BUSY);
	REG_WR(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, val);

	for (i = 0; i < 50; i++) {
		DELAY(10);

		val = REG_RD(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM);
		if (!(val & EMAC_MDIO_COMM_START_BUSY)) {
			*ret_val = (uint16_t)(val & EMAC_MDIO_COMM_DATA);
			DELAY(5);
			break;
		}
	}
	if (val & EMAC_MDIO_COMM_START_BUSY) {
		ELINK_DEBUG_P0(sc, "read phy register failed\n");

		*ret_val = 0;
		rc = ELINK_STATUS_TIMEOUT;
	}
	REG_WR(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE, mode);
	return rc;
}