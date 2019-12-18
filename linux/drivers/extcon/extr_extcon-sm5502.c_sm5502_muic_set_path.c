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
struct sm5502_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  DM_DP_SWITCH_AUDIO 135 
#define  DM_DP_SWITCH_OPEN 134 
#define  DM_DP_SWITCH_UART 133 
#define  DM_DP_SWITCH_USB 132 
 int EINVAL ; 
 int /*<<< orphan*/  SM5502_REG_MANUAL_SW1 ; 
 int SM5502_REG_MANUAL_SW1_DM_MASK ; 
 int SM5502_REG_MANUAL_SW1_DP_MASK ; 
 int SM5502_REG_MANUAL_SW1_VBUSIN_MASK ; 
#define  VBUSIN_SWITCH_MIC 131 
#define  VBUSIN_SWITCH_OPEN 130 
#define  VBUSIN_SWITCH_VBUSOUT 129 
#define  VBUSIN_SWITCH_VBUSOUT_WITH_USB 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int sm5502_muic_set_path(struct sm5502_muic_info *info,
				unsigned int con_sw, unsigned int vbus_sw,
				bool attached)
{
	int ret;

	if (!attached) {
		con_sw	= DM_DP_SWITCH_OPEN;
		vbus_sw	= VBUSIN_SWITCH_OPEN;
	}

	switch (con_sw) {
	case DM_DP_SWITCH_OPEN:
	case DM_DP_SWITCH_USB:
	case DM_DP_SWITCH_AUDIO:
	case DM_DP_SWITCH_UART:
		ret = regmap_update_bits(info->regmap, SM5502_REG_MANUAL_SW1,
					 SM5502_REG_MANUAL_SW1_DP_MASK |
					 SM5502_REG_MANUAL_SW1_DM_MASK,
					 con_sw);
		if (ret < 0) {
			dev_err(info->dev,
				"cannot update DM_CON/DP_CON switch\n");
			return ret;
		}
		break;
	default:
		dev_err(info->dev, "Unknown DM_CON/DP_CON switch type (%d)\n",
				con_sw);
		return -EINVAL;
	};

	switch (vbus_sw) {
	case VBUSIN_SWITCH_OPEN:
	case VBUSIN_SWITCH_VBUSOUT:
	case VBUSIN_SWITCH_MIC:
	case VBUSIN_SWITCH_VBUSOUT_WITH_USB:
		ret = regmap_update_bits(info->regmap, SM5502_REG_MANUAL_SW1,
					 SM5502_REG_MANUAL_SW1_VBUSIN_MASK,
					 vbus_sw);
		if (ret < 0) {
			dev_err(info->dev,
				"cannot update VBUSIN switch\n");
			return ret;
		}
		break;
	default:
		dev_err(info->dev, "Unknown VBUS switch type (%d)\n", vbus_sw);
		return -EINVAL;
	};

	return 0;
}