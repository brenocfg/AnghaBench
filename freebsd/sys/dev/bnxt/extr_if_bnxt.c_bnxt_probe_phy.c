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
struct bnxt_link_info {scalar_t__ auto_mode; int autoneg; int /*<<< orphan*/  force_link_speed; int /*<<< orphan*/  req_link_speed; int /*<<< orphan*/  auto_link_speed; int /*<<< orphan*/  duplex_setting; int /*<<< orphan*/  req_duplex; } ;
struct bnxt_softc {int /*<<< orphan*/  dev; struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int BNXT_AUTONEG_SPEED ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_AUTO_MODE_NONE ; 
 int bnxt_update_link (struct bnxt_softc*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bnxt_probe_phy(struct bnxt_softc *softc)
{
	struct bnxt_link_info *link_info = &softc->link_info;
	int rc = 0;

	rc = bnxt_update_link(softc, false);
	if (rc) {
		device_printf(softc->dev,
		    "Probe phy can't update link (rc: %x)\n", rc);
		return (rc);
	}

	/*initialize the ethool setting copy with NVM settings */
	if (link_info->auto_mode != HWRM_PORT_PHY_QCFG_OUTPUT_AUTO_MODE_NONE)
		link_info->autoneg |= BNXT_AUTONEG_SPEED;

	link_info->req_duplex = link_info->duplex_setting;
	if (link_info->autoneg & BNXT_AUTONEG_SPEED)
		link_info->req_link_speed = link_info->auto_link_speed;
	else
		link_info->req_link_speed = link_info->force_link_speed;
	return (rc);
}