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
typedef  int u8 ;
struct axp288_extcon_info {unsigned int previous_cable; int vbus_attach; int /*<<< orphan*/  dev; int /*<<< orphan*/  role_work; scalar_t__ role_sw; int /*<<< orphan*/  edev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP288_BC_DET_STAT_REG ; 
 int /*<<< orphan*/  AXP288_BC_GLOBAL_REG ; 
 int BC_GLOBAL_DET_STAT ; 
#define  DET_STAT_CDP 130 
#define  DET_STAT_DCP 129 
 int DET_STAT_MASK ; 
#define  DET_STAT_SDP 128 
 int DET_STAT_SHIFT ; 
 unsigned int EXTCON_CHG_USB_CDP ; 
 unsigned int EXTCON_CHG_USB_DCP ; 
 unsigned int EXTCON_CHG_USB_SDP ; 
 unsigned int EXTCON_USB ; 
 int axp288_get_vbus_attach (struct axp288_extcon_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  system_long_wq ; 

__attribute__((used)) static int axp288_handle_chrg_det_event(struct axp288_extcon_info *info)
{
	int ret, stat, cfg;
	u8 chrg_type;
	unsigned int cable = info->previous_cable;
	bool vbus_attach = false;

	vbus_attach = axp288_get_vbus_attach(info);
	if (!vbus_attach)
		goto no_vbus;

	/* Check charger detection completion status */
	ret = regmap_read(info->regmap, AXP288_BC_GLOBAL_REG, &cfg);
	if (ret < 0)
		goto dev_det_ret;
	if (cfg & BC_GLOBAL_DET_STAT) {
		dev_dbg(info->dev, "can't complete the charger detection\n");
		goto dev_det_ret;
	}

	ret = regmap_read(info->regmap, AXP288_BC_DET_STAT_REG, &stat);
	if (ret < 0)
		goto dev_det_ret;

	chrg_type = (stat & DET_STAT_MASK) >> DET_STAT_SHIFT;

	switch (chrg_type) {
	case DET_STAT_SDP:
		dev_dbg(info->dev, "sdp cable is connected\n");
		cable = EXTCON_CHG_USB_SDP;
		break;
	case DET_STAT_CDP:
		dev_dbg(info->dev, "cdp cable is connected\n");
		cable = EXTCON_CHG_USB_CDP;
		break;
	case DET_STAT_DCP:
		dev_dbg(info->dev, "dcp cable is connected\n");
		cable = EXTCON_CHG_USB_DCP;
		break;
	default:
		dev_warn(info->dev, "unknown (reserved) bc detect result\n");
		cable = EXTCON_CHG_USB_SDP;
	}

no_vbus:
	extcon_set_state_sync(info->edev, info->previous_cable, false);
	if (info->previous_cable == EXTCON_CHG_USB_SDP)
		extcon_set_state_sync(info->edev, EXTCON_USB, false);

	if (vbus_attach) {
		extcon_set_state_sync(info->edev, cable, vbus_attach);
		if (cable == EXTCON_CHG_USB_SDP)
			extcon_set_state_sync(info->edev, EXTCON_USB,
						vbus_attach);

		info->previous_cable = cable;
	}

	if (info->role_sw && info->vbus_attach != vbus_attach) {
		info->vbus_attach = vbus_attach;
		/* Setting the role can take a while */
		queue_work(system_long_wq, &info->role_work);
	}

	return 0;

dev_det_ret:
	if (ret < 0)
		dev_err(info->dev, "failed to detect BC Mod\n");

	return ret;
}