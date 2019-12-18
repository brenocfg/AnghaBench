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
struct TYPE_2__ {int tx_block; int /*<<< orphan*/  rx_callback; struct device* dev; } ;
struct rpi_firmware {int /*<<< orphan*/  c; int /*<<< orphan*/  chan; TYPE_1__ cl; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rpi_firmware* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rpi_firmware*) ; 
 int /*<<< orphan*/  response_callback ; 
 int /*<<< orphan*/  rpi_firmware_print_firmware_revision (struct rpi_firmware*) ; 
 int /*<<< orphan*/  rpi_register_clk_driver (struct device*) ; 
 int /*<<< orphan*/  rpi_register_hwmon_driver (struct device*,struct rpi_firmware*) ; 

__attribute__((used)) static int rpi_firmware_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rpi_firmware *fw;

	fw = devm_kzalloc(dev, sizeof(*fw), GFP_KERNEL);
	if (!fw)
		return -ENOMEM;

	fw->cl.dev = dev;
	fw->cl.rx_callback = response_callback;
	fw->cl.tx_block = true;

	fw->chan = mbox_request_channel(&fw->cl, 0);
	if (IS_ERR(fw->chan)) {
		int ret = PTR_ERR(fw->chan);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get mbox channel: %d\n", ret);
		return ret;
	}

	init_completion(&fw->c);

	platform_set_drvdata(pdev, fw);

	rpi_firmware_print_firmware_revision(fw);
	rpi_register_hwmon_driver(dev, fw);
	rpi_register_clk_driver(dev);

	return 0;
}