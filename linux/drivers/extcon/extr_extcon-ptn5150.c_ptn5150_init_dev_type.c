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
struct ptn5150_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PTN5150_REG_DEVICE_ID ; 
 unsigned int PTN5150_REG_DEVICE_ID_VENDOR_MASK ; 
 unsigned int PTN5150_REG_DEVICE_ID_VENDOR_SHIFT ; 
 unsigned int PTN5150_REG_DEVICE_ID_VERSION_MASK ; 
 unsigned int PTN5150_REG_DEVICE_ID_VERSION_SHIFT ; 
 int /*<<< orphan*/  PTN5150_REG_INT_REG_STATUS ; 
 int /*<<< orphan*/  PTN5150_REG_INT_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ptn5150_init_dev_type(struct ptn5150_info *info)
{
	unsigned int reg_data, vendor_id, version_id;
	int ret;

	ret = regmap_read(info->regmap, PTN5150_REG_DEVICE_ID, &reg_data);
	if (ret) {
		dev_err(info->dev, "failed to read DEVICE_ID %d\n", ret);
		return -EINVAL;
	}

	vendor_id = ((reg_data & PTN5150_REG_DEVICE_ID_VENDOR_MASK) >>
				PTN5150_REG_DEVICE_ID_VENDOR_SHIFT);
	version_id = ((reg_data & PTN5150_REG_DEVICE_ID_VERSION_MASK) >>
				PTN5150_REG_DEVICE_ID_VERSION_SHIFT);

	dev_info(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
			    version_id, vendor_id);

	/* Clear any existing interrupts */
	ret = regmap_read(info->regmap, PTN5150_REG_INT_STATUS, &reg_data);
	if (ret) {
		dev_err(info->dev,
			"failed to read PTN5150_REG_INT_STATUS %d\n",
			ret);
		return -EINVAL;
	}

	ret = regmap_read(info->regmap, PTN5150_REG_INT_REG_STATUS, &reg_data);
	if (ret) {
		dev_err(info->dev,
			"failed to read PTN5150_REG_INT_REG_STATUS %d\n", ret);
		return -EINVAL;
	}

	return 0;
}