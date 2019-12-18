#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  enables; int /*<<< orphan*/  force_pause; int /*<<< orphan*/  auto_pause; } ;
struct TYPE_2__ {scalar_t__ tx; scalar_t__ rx; scalar_t__ autoneg; } ;
struct bnxt_link_info {TYPE_1__ flow_ctrl; } ;
struct bnxt_softc {struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_AUTO_PAUSE_AUTONEG_PAUSE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_AUTO_PAUSE_RX ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_AUTO_PAUSE_TX ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_ENABLES_AUTO_PAUSE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_ENABLES_FORCE_PAUSE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_PAUSE_RX ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_PAUSE_TX ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_hwrm_set_pause_common(struct bnxt_softc *softc,
    struct hwrm_port_phy_cfg_input *req)
{
	struct bnxt_link_info *link_info = &softc->link_info;

	if (link_info->flow_ctrl.autoneg) {
		req->auto_pause =
		    HWRM_PORT_PHY_CFG_INPUT_AUTO_PAUSE_AUTONEG_PAUSE;
		if (link_info->flow_ctrl.rx)
			req->auto_pause |=
			    HWRM_PORT_PHY_CFG_INPUT_AUTO_PAUSE_RX;
		if (link_info->flow_ctrl.tx)
			req->auto_pause |=
			    HWRM_PORT_PHY_CFG_INPUT_AUTO_PAUSE_TX;
		req->enables |=
		    htole32(HWRM_PORT_PHY_CFG_INPUT_ENABLES_AUTO_PAUSE);
	} else {
		if (link_info->flow_ctrl.rx)
			req->force_pause |=
			    HWRM_PORT_PHY_CFG_INPUT_FORCE_PAUSE_RX;
		if (link_info->flow_ctrl.tx)
			req->force_pause |=
			    HWRM_PORT_PHY_CFG_INPUT_FORCE_PAUSE_TX;
		req->enables |=
			htole32(HWRM_PORT_PHY_CFG_INPUT_ENABLES_FORCE_PAUSE);
	}
}