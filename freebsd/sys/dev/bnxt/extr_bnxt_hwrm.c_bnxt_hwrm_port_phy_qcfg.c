#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hwrm_port_phy_qcfg_output {scalar_t__ link; int auto_pause; int force_pause; int phy_maj; int phy_min; int phy_bld; int eee_config_phy_addr; int /*<<< orphan*/  xcvr_pkg_type; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  media_type; int /*<<< orphan*/  phy_vendor_partnumber; int /*<<< orphan*/  phy_vendor_name; int /*<<< orphan*/  preemphasis; int /*<<< orphan*/  auto_link_speed_mask; int /*<<< orphan*/  support_speeds; int /*<<< orphan*/  auto_link_speed; int /*<<< orphan*/  force_link_speed; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  duplex_cfg; scalar_t__ auto_mode; } ;
struct hwrm_port_phy_qcfg_input {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ idi_vaddr; } ;
struct TYPE_5__ {int autoneg; int tx; int rx; } ;
struct bnxt_link_info {scalar_t__ phy_link_status; int* phy_ver; int phy_addr; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  media_type; int /*<<< orphan*/  preemphasis; void* auto_link_speeds; void* support_speeds; void* auto_link_speed; void* force_link_speed; void* link_speed; int /*<<< orphan*/  duplex_setting; TYPE_2__ flow_ctrl; scalar_t__ auto_mode; int /*<<< orphan*/  duplex; } ;
struct bnxt_softc {TYPE_3__* ver_info; TYPE_1__ hwrm_cmd_resp; struct bnxt_link_info link_info; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_6__ {int /*<<< orphan*/  phy_partnumber; int /*<<< orphan*/  phy_vendor; int /*<<< orphan*/  phy_ver; } ;

/* Variables and functions */
 int BNXT_AUTO_PAUSE_AUTONEG_PAUSE ; 
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_NAME_SIZE ; 
 int BNXT_PAUSE_RX ; 
 int BNXT_PAUSE_TX ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_QCFG ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_LINK_LINK ; 
 int HWRM_PORT_PHY_QCFG_OUTPUT_PHY_ADDR_MASK ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_port_phy_qcfg_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_port_phy_qcfg_input*,int /*<<< orphan*/ ) ; 
 void* le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_port_phy_qcfg(struct bnxt_softc *softc)
{
	struct bnxt_link_info *link_info = &softc->link_info;
	struct hwrm_port_phy_qcfg_input req = {0};
	struct hwrm_port_phy_qcfg_output *resp =
	    (void *)softc->hwrm_cmd_resp.idi_vaddr;
	int rc = 0;

	BNXT_HWRM_LOCK(softc);
	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_PORT_PHY_QCFG);

	rc = _hwrm_send_message(softc, &req, sizeof(req));
	if (rc)
		goto exit;

	link_info->phy_link_status = resp->link;
	link_info->duplex =  resp->duplex_cfg;
	link_info->auto_mode = resp->auto_mode;

        /*
         * When AUTO_PAUSE_AUTONEG_PAUSE bit is set to 1, 
         * the advertisement of pause is enabled.
         * 1. When the auto_mode is not set to none and this flag is set to 1,
         *    then the auto_pause bits on this port are being advertised and
         *    autoneg pause results are being interpreted.
         * 2. When the auto_mode is not set to none and this flag is set to 0,
         *    the pause is forced as indicated in force_pause, and also 
	 *    advertised as auto_pause bits, but the autoneg results are not 
	 *    interpreted since the pause configuration is being forced.
         * 3. When the auto_mode is set to none and this flag is set to 1,
         *    auto_pause bits should be ignored and should be set to 0.
         */
	
	link_info->flow_ctrl.autoneg = false;
	link_info->flow_ctrl.tx = false;
	link_info->flow_ctrl.rx = false;

	if ((resp->auto_mode) && 
            (resp->auto_pause & BNXT_AUTO_PAUSE_AUTONEG_PAUSE)) {
			link_info->flow_ctrl.autoneg = true;
	}

	if (link_info->flow_ctrl.autoneg) {
		if (resp->auto_pause & BNXT_PAUSE_TX)
			link_info->flow_ctrl.tx = true;
		if (resp->auto_pause & BNXT_PAUSE_RX)
			link_info->flow_ctrl.rx = true;
	} else {
		if (resp->force_pause & BNXT_PAUSE_TX)
			link_info->flow_ctrl.tx = true;
		if (resp->force_pause & BNXT_PAUSE_RX)
			link_info->flow_ctrl.rx = true;
	}

	link_info->duplex_setting = resp->duplex_cfg;
	if (link_info->phy_link_status == HWRM_PORT_PHY_QCFG_OUTPUT_LINK_LINK)
		link_info->link_speed = le16toh(resp->link_speed);
	else
		link_info->link_speed = 0;
	link_info->force_link_speed = le16toh(resp->force_link_speed);
	link_info->auto_link_speed = le16toh(resp->auto_link_speed);
	link_info->support_speeds = le16toh(resp->support_speeds);
	link_info->auto_link_speeds = le16toh(resp->auto_link_speed_mask);
	link_info->preemphasis = le32toh(resp->preemphasis);
	link_info->phy_ver[0] = resp->phy_maj;
	link_info->phy_ver[1] = resp->phy_min;
	link_info->phy_ver[2] = resp->phy_bld;
	snprintf(softc->ver_info->phy_ver, sizeof(softc->ver_info->phy_ver),
	    "%d.%d.%d", link_info->phy_ver[0], link_info->phy_ver[1],
	    link_info->phy_ver[2]);
	strlcpy(softc->ver_info->phy_vendor, resp->phy_vendor_name,
	    BNXT_NAME_SIZE);
	strlcpy(softc->ver_info->phy_partnumber, resp->phy_vendor_partnumber,
	    BNXT_NAME_SIZE);
	link_info->media_type = resp->media_type;
	link_info->phy_type = resp->phy_type;
	link_info->transceiver = resp->xcvr_pkg_type;
	link_info->phy_addr = resp->eee_config_phy_addr &
	    HWRM_PORT_PHY_QCFG_OUTPUT_PHY_ADDR_MASK;

exit:
	BNXT_HWRM_UNLOCK(softc);
	return rc;
}