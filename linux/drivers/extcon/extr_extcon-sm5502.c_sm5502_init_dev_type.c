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
struct sm5502_muic_info {int num_reg_data; TYPE_1__* reg_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int val; int /*<<< orphan*/  reg; int /*<<< orphan*/  invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM5502_REG_DEVICE_ID ; 
 unsigned int SM5502_REG_DEVICE_ID_VENDOR_MASK ; 
 unsigned int SM5502_REG_DEVICE_ID_VENDOR_SHIFT ; 
 unsigned int SM5502_REG_DEVICE_ID_VERSION_MASK ; 
 unsigned int SM5502_REG_DEVICE_ID_VERSION_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sm5502_init_dev_type(struct sm5502_muic_info *info)
{
	unsigned int reg_data, vendor_id, version_id;
	int i, ret;

	/* To test I2C, Print version_id and vendor_id of SM5502 */
	ret = regmap_read(info->regmap, SM5502_REG_DEVICE_ID, &reg_data);
	if (ret) {
		dev_err(info->dev,
			"failed to read DEVICE_ID register: %d\n", ret);
		return;
	}

	vendor_id = ((reg_data & SM5502_REG_DEVICE_ID_VENDOR_MASK) >>
				SM5502_REG_DEVICE_ID_VENDOR_SHIFT);
	version_id = ((reg_data & SM5502_REG_DEVICE_ID_VERSION_MASK) >>
				SM5502_REG_DEVICE_ID_VERSION_SHIFT);

	dev_info(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
			    version_id, vendor_id);

	/* Initiazle the register of SM5502 device to bring-up */
	for (i = 0; i < info->num_reg_data; i++) {
		unsigned int val = 0;

		if (!info->reg_data[i].invert)
			val |= ~info->reg_data[i].val;
		else
			val = info->reg_data[i].val;
		regmap_write(info->regmap, info->reg_data[i].reg, val);
	}
}