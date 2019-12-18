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
struct sec_dev_info {int /*<<< orphan*/  dev; int /*<<< orphan*/ * regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int SEC_NUM_ADDR_REGIONS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int sec_map_io(struct sec_dev_info *info, struct platform_device *pdev)
{
	struct resource *res;
	int i;

	for (i = 0; i < SEC_NUM_ADDR_REGIONS; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);

		if (!res) {
			dev_err(info->dev, "Memory resource %d not found\n", i);
			return -EINVAL;
		}

		info->regs[i] = devm_ioremap(info->dev, res->start,
					     resource_size(res));
		if (!info->regs[i]) {
			dev_err(info->dev,
				"Memory resource %d could not be remapped\n",
				i);
			return -EINVAL;
		}
	}

	return 0;
}