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
struct elink_phy {int type; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 130 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 129 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT 128 
 int /*<<< orphan*/  elink_8727_power_module (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_warpcore_power_module (struct elink_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_power_sfp_module(struct elink_params *params,
				   struct elink_phy *phy,
				   uint8_t power)
{
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P1(sc, "Setting SFP+ power to %x\n", power);

	switch (phy->type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		elink_8727_power_module(params->sc, phy, power);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT:
		elink_warpcore_power_module(params, power);
		break;
	default:
		break;
	}
}