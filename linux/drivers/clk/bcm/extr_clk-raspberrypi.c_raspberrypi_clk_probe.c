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
struct rpi_firmware {int dummy; } ;
struct raspberrypi_clk {int /*<<< orphan*/  cpufreq; struct rpi_firmware* firmware; struct device* dev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct raspberrypi_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct raspberrypi_clk*) ; 
 int raspberrypi_register_pllb (struct raspberrypi_clk*) ; 
 int raspberrypi_register_pllb_arm (struct raspberrypi_clk*) ; 
 struct rpi_firmware* rpi_firmware_get (struct device_node*) ; 

__attribute__((used)) static int raspberrypi_clk_probe(struct platform_device *pdev)
{
	struct device_node *firmware_node;
	struct device *dev = &pdev->dev;
	struct rpi_firmware *firmware;
	struct raspberrypi_clk *rpi;
	int ret;

	firmware_node = of_find_compatible_node(NULL, NULL,
					"raspberrypi,bcm2835-firmware");
	if (!firmware_node) {
		dev_err(dev, "Missing firmware node\n");
		return -ENOENT;
	}

	firmware = rpi_firmware_get(firmware_node);
	of_node_put(firmware_node);
	if (!firmware)
		return -EPROBE_DEFER;

	rpi = devm_kzalloc(dev, sizeof(*rpi), GFP_KERNEL);
	if (!rpi)
		return -ENOMEM;

	rpi->dev = dev;
	rpi->firmware = firmware;
	platform_set_drvdata(pdev, rpi);

	ret = raspberrypi_register_pllb(rpi);
	if (ret) {
		dev_err(dev, "Failed to initialize pllb, %d\n", ret);
		return ret;
	}

	ret = raspberrypi_register_pllb_arm(rpi);
	if (ret)
		return ret;

	rpi->cpufreq = platform_device_register_data(dev, "raspberrypi-cpufreq",
						     -1, NULL, 0);

	return 0;
}