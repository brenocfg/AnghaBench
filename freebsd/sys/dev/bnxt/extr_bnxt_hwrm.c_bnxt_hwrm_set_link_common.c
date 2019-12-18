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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct hwrm_port_phy_cfg_input {int /*<<< orphan*/  flags; int /*<<< orphan*/  force_link_speed; int /*<<< orphan*/  enables; int /*<<< orphan*/  auto_mode; } ;
struct TYPE_2__ {int autoneg; int /*<<< orphan*/  req_link_speed; } ;
struct bnxt_softc {TYPE_1__ link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_SPEED ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_AUTO_MODE_ALL_SPEEDS ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_ENABLES_AUTO_MODE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FLAGS_FORCE ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FLAGS_RESET_PHY ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FLAGS_RESTART_AUTONEG ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_hwrm_set_link_common(struct bnxt_softc *softc,
    struct hwrm_port_phy_cfg_input *req)
{
	uint8_t autoneg = softc->link_info.autoneg;
	uint16_t fw_link_speed = softc->link_info.req_link_speed;

	if (autoneg & BNXT_AUTONEG_SPEED) {
		req->auto_mode |=
		    HWRM_PORT_PHY_CFG_INPUT_AUTO_MODE_ALL_SPEEDS;

		req->enables |=
		    htole32(HWRM_PORT_PHY_CFG_INPUT_ENABLES_AUTO_MODE);
		req->flags |=
		    htole32(HWRM_PORT_PHY_CFG_INPUT_FLAGS_RESTART_AUTONEG);
	} else {
		req->force_link_speed = htole16(fw_link_speed);
		req->flags |= htole32(HWRM_PORT_PHY_CFG_INPUT_FLAGS_FORCE);
	}

	/* tell chimp that the setting takes effect immediately */
	req->flags |= htole32(HWRM_PORT_PHY_CFG_INPUT_FLAGS_RESET_PHY);
}