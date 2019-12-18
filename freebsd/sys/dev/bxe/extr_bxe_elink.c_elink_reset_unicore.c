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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {int /*<<< orphan*/  port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_LOG_ID_PHY_UNINITIALIZED ; 
 scalar_t__ ELINK_MDIO_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_MII_CONTROL ; 
 scalar_t__ MDIO_COMBO_IEEO_MII_CONTROL_RESET ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  elink_cb_event_log (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_serdes_access (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static elink_status_t elink_reset_unicore(struct elink_params *params,
			       struct elink_phy *phy,
			       uint8_t set_serdes)
{
	struct bxe_softc *sc = params->sc;
	uint16_t mii_control;
	uint16_t i;
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, &mii_control);

	/* Reset the unicore */
	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL,
			  (mii_control |
			   MDIO_COMBO_IEEO_MII_CONTROL_RESET));
	if (set_serdes)
		elink_set_serdes_access(sc, params->port);

	/* Wait for the reset to self clear */
	for (i = 0; i < ELINK_MDIO_ACCESS_TIMEOUT; i++) {
		DELAY(5);

		/* The reset erased the previous bank value */
		CL22_RD_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  &mii_control);

		if (!(mii_control & MDIO_COMBO_IEEO_MII_CONTROL_RESET)) {
			DELAY(5);
			return ELINK_STATUS_OK;
		}
	}

	elink_cb_event_log(sc, ELINK_LOG_ID_PHY_UNINITIALIZED, params->port); // "Warning: PHY was not initialized,"
			     // " Port %d\n",

	ELINK_DEBUG_P0(sc, "BUG! XGXS is still in reset!\n");
	return ELINK_STATUS_ERROR;

}