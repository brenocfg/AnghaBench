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
typedef  int u8 ;
struct max14577_muic_info {int /*<<< orphan*/  dev; TYPE_1__* max14577; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CLEAR_IDBEN_MICEN_MASK ; 
 int CTRL1_SW_OPEN ; 
 int CTRL2_CPEN_MASK ; 
 int CTRL2_LOWPWR_MASK ; 
 int /*<<< orphan*/  MAX14577_MUIC_REG_CONTROL1 ; 
 int /*<<< orphan*/  MAX14577_REG_CONTROL2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int max14577_update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max14577_muic_set_path(struct max14577_muic_info *info,
		u8 val, bool attached)
{
	u8 ctrl1, ctrl2 = 0;
	int ret;

	/* Set open state to path before changing hw path */
	ret = max14577_update_reg(info->max14577->regmap,
				MAX14577_MUIC_REG_CONTROL1,
				CLEAR_IDBEN_MICEN_MASK, CTRL1_SW_OPEN);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	if (attached)
		ctrl1 = val;
	else
		ctrl1 = CTRL1_SW_OPEN;

	ret = max14577_update_reg(info->max14577->regmap,
				MAX14577_MUIC_REG_CONTROL1,
				CLEAR_IDBEN_MICEN_MASK, ctrl1);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	if (attached)
		ctrl2 |= CTRL2_CPEN_MASK;	/* LowPwr=0, CPEn=1 */
	else
		ctrl2 |= CTRL2_LOWPWR_MASK;	/* LowPwr=1, CPEn=0 */

	ret = max14577_update_reg(info->max14577->regmap,
			MAX14577_REG_CONTROL2,
			CTRL2_LOWPWR_MASK | CTRL2_CPEN_MASK, ctrl2);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	dev_dbg(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	return 0;
}