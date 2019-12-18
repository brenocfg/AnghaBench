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
struct stratix10_rsu_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_RSU_UPDATE ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct stratix10_rsu_priv* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  rsu_command_callback ; 
 int rsu_send_msg (struct stratix10_rsu_priv*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t reboot_image_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct stratix10_rsu_priv *priv = dev_get_drvdata(dev);
	unsigned long address;
	int ret;

	if (priv == 0)
		return -ENODEV;

	ret = kstrtoul(buf, 0, &address);
	if (ret)
		return ret;

	ret = rsu_send_msg(priv, COMMAND_RSU_UPDATE,
			   address, rsu_command_callback);
	if (ret) {
		dev_err(dev, "Error, RSU update returned %i\n", ret);
		return ret;
	}

	return count;
}