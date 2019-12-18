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
typedef  int uint16_t ;
struct elink_phy {int flags; int addr; scalar_t__ mdio_ctrl; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_FLAGS_DUMMY_READ ; 
 int ELINK_FLAGS_MDC_MDIO_WA ; 
 int ELINK_FLAGS_MDC_MDIO_WA_B0 ; 
 int ELINK_FLAGS_MDC_MDIO_WA_G ; 
 int /*<<< orphan*/  ELINK_LOG_ID_MDIO_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  ELINK_STATUS_TIMEOUT ; 
 int EMAC_MDIO_COMM_COMMAND_ADDRESS ; 
 int EMAC_MDIO_COMM_COMMAND_WRITE_45 ; 
 int EMAC_MDIO_COMM_START_BUSY ; 
 int /*<<< orphan*/  EMAC_MDIO_STATUS_10MB ; 
 scalar_t__ EMAC_REG_EMAC_MDIO_COMM ; 
 scalar_t__ EMAC_REG_EMAC_MDIO_STATUS ; 
 scalar_t__ MISC_REG_CHIP_NUM ; 
 scalar_t__ MISC_REG_CHIP_REV ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_bits_dis (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_bits_en (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_cb_event_log (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int,int,int*) ; 
 int /*<<< orphan*/  elink_set_mdio_clk (struct bxe_softc*,int,scalar_t__) ; 

__attribute__((used)) static elink_status_t elink_cl45_write(struct bxe_softc *sc, struct elink_phy *phy,
			    uint8_t devad, uint16_t reg, uint16_t val)
{
	uint32_t tmp;
	uint8_t i;
	elink_status_t rc = ELINK_STATUS_OK;
	uint32_t chip_id;
	if (phy->flags & ELINK_FLAGS_MDC_MDIO_WA_G) {
		chip_id = (REG_RD(sc, MISC_REG_CHIP_NUM) << 16) |
			  ((REG_RD(sc, MISC_REG_CHIP_REV) & 0xf) << 12);
		elink_set_mdio_clk(sc, chip_id, phy->mdio_ctrl);
	}

	if (phy->flags & ELINK_FLAGS_MDC_MDIO_WA_B0)
		elink_bits_en(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_STATUS,
			      EMAC_MDIO_STATUS_10MB);

	/* Address */
	tmp = ((phy->addr << 21) | (devad << 16) | reg |
	       EMAC_MDIO_COMM_COMMAND_ADDRESS |
	       EMAC_MDIO_COMM_START_BUSY);
	REG_WR(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, tmp);

	for (i = 0; i < 50; i++) {
		DELAY(10);

		tmp = REG_RD(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM);
		if (!(tmp & EMAC_MDIO_COMM_START_BUSY)) {
			DELAY(5);
			break;
		}
	}
	if (tmp & EMAC_MDIO_COMM_START_BUSY) {
		ELINK_DEBUG_P0(sc, "write phy register failed\n");
		elink_cb_event_log(sc, ELINK_LOG_ID_MDIO_ACCESS_TIMEOUT); // "MDC/MDIO access timeout\n"

		rc = ELINK_STATUS_TIMEOUT;
	} else {
		/* Data */
		tmp = ((phy->addr << 21) | (devad << 16) | val |
		       EMAC_MDIO_COMM_COMMAND_WRITE_45 |
		       EMAC_MDIO_COMM_START_BUSY);
		REG_WR(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, tmp);

		for (i = 0; i < 50; i++) {
			DELAY(10);

			tmp = REG_RD(sc, phy->mdio_ctrl +
				     EMAC_REG_EMAC_MDIO_COMM);
			if (!(tmp & EMAC_MDIO_COMM_START_BUSY)) {
				DELAY(5);
				break;
			}
		}
		if (tmp & EMAC_MDIO_COMM_START_BUSY) {
			ELINK_DEBUG_P0(sc, "write phy register failed\n");
			elink_cb_event_log(sc, ELINK_LOG_ID_MDIO_ACCESS_TIMEOUT); // "MDC/MDIO access timeout\n"

			rc = ELINK_STATUS_TIMEOUT;
		}
	}
	/* Work around for E3 A0 */
	if (phy->flags & ELINK_FLAGS_MDC_MDIO_WA) {
		phy->flags ^= ELINK_FLAGS_DUMMY_READ;
		if (phy->flags & ELINK_FLAGS_DUMMY_READ) {
			uint16_t temp_val;
			elink_cl45_read(sc, phy, devad, 0xf, &temp_val);
		}
	}
	if (phy->flags & ELINK_FLAGS_MDC_MDIO_WA_B0)
		elink_bits_dis(sc, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_STATUS,
			       EMAC_MDIO_STATUS_10MB);
	return rc;
}