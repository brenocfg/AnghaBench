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
typedef  int /*<<< orphan*/  u8 ;
struct rt8973a_muic_info {int num_reg_data; int auto_config; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; TYPE_1__* reg_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; scalar_t__ invert; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT8973A_REG_CONTROL1 ; 
 unsigned int RT8973A_REG_CONTROL1_AUTO_CONFIG_MASK ; 
 int /*<<< orphan*/  RT8973A_REG_DEVICE_ID ; 
 unsigned int RT8973A_REG_DEVICE_ID_VENDOR_MASK ; 
 unsigned int RT8973A_REG_DEVICE_ID_VENDOR_SHIFT ; 
 unsigned int RT8973A_REG_DEVICE_ID_VERSION_MASK ; 
 unsigned int RT8973A_REG_DEVICE_ID_VERSION_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt8973a_init_dev_type(struct rt8973a_muic_info *info)
{
	unsigned int data, vendor_id, version_id;
	int i, ret;

	/* To test I2C, Print version_id and vendor_id of RT8973A */
	ret = regmap_read(info->regmap, RT8973A_REG_DEVICE_ID, &data);
	if (ret) {
		dev_err(info->dev,
			"failed to read DEVICE_ID register: %d\n", ret);
		return;
	}

	vendor_id = ((data & RT8973A_REG_DEVICE_ID_VENDOR_MASK) >>
				RT8973A_REG_DEVICE_ID_VENDOR_SHIFT);
	version_id = ((data & RT8973A_REG_DEVICE_ID_VERSION_MASK) >>
				RT8973A_REG_DEVICE_ID_VERSION_SHIFT);

	dev_info(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
			    version_id, vendor_id);

	/* Initiazle the register of RT8973A device to bring-up */
	for (i = 0; i < info->num_reg_data; i++) {
		u8 reg = info->reg_data[i].reg;
		u8 mask = info->reg_data[i].mask;
		u8 val = 0;

		if (info->reg_data[i].invert)
			val = ~info->reg_data[i].val;
		else
			val = info->reg_data[i].val;

		regmap_update_bits(info->regmap, reg, mask, val);
	}

	/* Check whether RT8973A is auto switching mode or not */
	ret = regmap_read(info->regmap, RT8973A_REG_CONTROL1, &data);
	if (ret) {
		dev_err(info->dev,
			"failed to read CONTROL1 register: %d\n", ret);
		return;
	}

	data &= RT8973A_REG_CONTROL1_AUTO_CONFIG_MASK;
	if (data) {
		info->auto_config = true;
		dev_info(info->dev,
			"Enable Auto-configuration for internal path\n");
	}
}