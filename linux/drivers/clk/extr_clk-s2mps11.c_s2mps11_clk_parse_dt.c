#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sec_pmic_dev {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct clk_init_data {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct device_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S2MPS11_CLKS_NUM ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct sec_pmic_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_string_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct device_node *s2mps11_clk_parse_dt(struct platform_device *pdev,
		struct clk_init_data *clks_init)
{
	struct sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct device_node *clk_np;
	int i;

	if (!iodev->dev->of_node)
		return ERR_PTR(-EINVAL);

	clk_np = of_get_child_by_name(iodev->dev->of_node, "clocks");
	if (!clk_np) {
		dev_err(&pdev->dev, "could not find clock sub-node\n");
		return ERR_PTR(-EINVAL);
	}

	for (i = 0; i < S2MPS11_CLKS_NUM; i++)
		of_property_read_string_index(clk_np, "clock-output-names", i,
				&clks_init[i].name);

	return clk_np;
}