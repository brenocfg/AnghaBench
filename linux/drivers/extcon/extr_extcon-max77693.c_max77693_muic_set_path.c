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
typedef  unsigned int u8 ;
struct max77693_muic_info {int /*<<< orphan*/  dev; TYPE_1__* max77693; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap_muic; } ;

/* Variables and functions */
 unsigned int COMP_SW_MASK ; 
 unsigned int MAX77693_CONTROL1_SW_OPEN ; 
 unsigned int MAX77693_CONTROL2_CPEN_MASK ; 
 unsigned int MAX77693_CONTROL2_LOWPWR_MASK ; 
 int /*<<< orphan*/  MAX77693_MUIC_REG_CTRL1 ; 
 int /*<<< orphan*/  MAX77693_MUIC_REG_CTRL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int max77693_muic_set_path(struct max77693_muic_info *info,
		u8 val, bool attached)
{
	int ret;
	unsigned int ctrl1, ctrl2 = 0;

	if (attached)
		ctrl1 = val;
	else
		ctrl1 = MAX77693_CONTROL1_SW_OPEN;

	ret = regmap_update_bits(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_CTRL1, COMP_SW_MASK, ctrl1);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	if (attached)
		ctrl2 |= MAX77693_CONTROL2_CPEN_MASK;	/* LowPwr=0, CPEn=1 */
	else
		ctrl2 |= MAX77693_CONTROL2_LOWPWR_MASK;	/* LowPwr=1, CPEn=0 */

	ret = regmap_update_bits(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_CTRL2,
			MAX77693_CONTROL2_LOWPWR_MASK | MAX77693_CONTROL2_CPEN_MASK,
			ctrl2);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	dev_info(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	return 0;
}