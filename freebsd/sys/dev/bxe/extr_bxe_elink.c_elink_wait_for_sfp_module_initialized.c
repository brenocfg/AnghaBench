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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct elink_phy {scalar_t__ type; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_I2C_DEV_ADDR_A0 ; 
 scalar_t__ ELINK_STATUS_OK ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 
 scalar_t__ elink_read_sfp_module_eeprom (struct elink_phy*,struct elink_params*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ elink_warpcore_read_sfp_module_eeprom (struct elink_phy*,struct elink_params*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static elink_status_t elink_wait_for_sfp_module_initialized(struct elink_phy *phy,
						 struct elink_params *params)

{
	uint8_t val;
	elink_status_t rc;
	struct bxe_softc *sc = params->sc;
	uint16_t timeout;
	/* Initialization time after hot-plug may take up to 300ms for
	 * some phys type ( e.g. JDSU )
	 */

	for (timeout = 0; timeout < 60; timeout++) {
		if (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT)
			rc = elink_warpcore_read_sfp_module_eeprom(
				phy, params, ELINK_I2C_DEV_ADDR_A0, 1, 1, &val,
				1);
		else
			rc = elink_read_sfp_module_eeprom(phy, params,
							  ELINK_I2C_DEV_ADDR_A0,
							  1, 1, &val);
		if (rc == 0) {
			ELINK_DEBUG_P1(sc,
			   "SFP+ module initialization took %d ms\n",
			   timeout * 5);
			return ELINK_STATUS_OK;
		}
		DELAY(1000 * 5);
	}
	rc = elink_read_sfp_module_eeprom(phy, params, ELINK_I2C_DEV_ADDR_A0,
					  1, 1, &val);
	return rc;
}