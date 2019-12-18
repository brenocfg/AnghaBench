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
typedef  int /*<<< orphan*/  uint16_t ;
struct elink_phy {int type; } ;
struct elink_params {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 131 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726 130 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 129 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT 128 
 int /*<<< orphan*/  elink_8726_set_limiting_mode (int /*<<< orphan*/ ,struct elink_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_8727_set_limiting_mode (int /*<<< orphan*/ ,struct elink_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_warpcore_set_limiting_mode (struct elink_params*,struct elink_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_set_limiting_mode(struct elink_params *params,
				    struct elink_phy *phy,
				    uint16_t edc_mode)
{
	switch (phy->type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		elink_8726_set_limiting_mode(params->sc, phy, edc_mode);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		elink_8727_set_limiting_mode(params->sc, phy, edc_mode);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT:
		elink_warpcore_set_limiting_mode(params, phy, edc_mode);
		break;
	}
}