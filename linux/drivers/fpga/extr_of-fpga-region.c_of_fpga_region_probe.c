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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct fpga_region {int /*<<< orphan*/  dev; } ;
struct fpga_manager {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct fpga_manager*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct fpga_region* devm_fpga_region_create (struct device*,struct fpga_manager*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_mgr_put (struct fpga_manager*) ; 
 int /*<<< orphan*/  fpga_region_of_match ; 
 int fpga_region_register (struct fpga_region*) ; 
 int /*<<< orphan*/  of_fpga_region_get_bridges ; 
 struct fpga_manager* of_fpga_region_get_mgr (struct device_node*) ; 
 int /*<<< orphan*/  of_platform_populate (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_region*) ; 

__attribute__((used)) static int of_fpga_region_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct fpga_region *region;
	struct fpga_manager *mgr;
	int ret;

	/* Find the FPGA mgr specified by region or parent region. */
	mgr = of_fpga_region_get_mgr(np);
	if (IS_ERR(mgr))
		return -EPROBE_DEFER;

	region = devm_fpga_region_create(dev, mgr, of_fpga_region_get_bridges);
	if (!region) {
		ret = -ENOMEM;
		goto eprobe_mgr_put;
	}

	ret = fpga_region_register(region);
	if (ret)
		goto eprobe_mgr_put;

	of_platform_populate(np, fpga_region_of_match, NULL, &region->dev);
	platform_set_drvdata(pdev, region);

	dev_info(dev, "FPGA Region probed\n");

	return 0;

eprobe_mgr_put:
	fpga_mgr_put(mgr);
	return ret;
}