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
struct mcu {int reg_ctrl; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  MCU_REG_CTRL ; 
 struct mcu* glob_mcu ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_status(struct device *d,
			   struct device_attribute *attr, char *buf)
{
	int ret;
	struct mcu *mcu = glob_mcu;

	ret = i2c_smbus_read_byte_data(mcu->client, MCU_REG_CTRL);
	if (ret < 0)
		return -ENODEV;
	mcu->reg_ctrl = ret;

	return sprintf(buf, "%02x\n", ret);
}