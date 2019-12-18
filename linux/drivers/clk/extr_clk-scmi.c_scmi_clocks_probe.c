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
struct scmi_handle {TYPE_1__* clk_ops; } ;
struct device {struct device_node* of_node; } ;
struct scmi_device {struct scmi_handle* handle; struct device dev; } ;
struct clk_hw {int dummy; } ;
struct scmi_clk {int id; struct clk_hw hw; TYPE_2__* info; struct scmi_handle const* handle; } ;
struct device_node {int dummy; } ;
struct clk_hw_onecell_data {int num; struct clk_hw** hws; } ;
struct TYPE_4__ {int name; } ;
struct TYPE_3__ {int (* count_get ) (struct scmi_handle const*) ;TYPE_2__* (* info_get ) (struct scmi_handle const*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct scmi_clk*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,struct clk_hw_onecell_data*) ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 int scmi_clk_ops_init (struct device*,struct scmi_clk*) ; 
 int struct_size (struct clk_hw_onecell_data*,struct clk_hw**,int) ; 
 int stub1 (struct scmi_handle const*) ; 
 TYPE_2__* stub2 (struct scmi_handle const*,int) ; 

__attribute__((used)) static int scmi_clocks_probe(struct scmi_device *sdev)
{
	int idx, count, err;
	struct clk_hw **hws;
	struct clk_hw_onecell_data *clk_data;
	struct device *dev = &sdev->dev;
	struct device_node *np = dev->of_node;
	const struct scmi_handle *handle = sdev->handle;

	if (!handle || !handle->clk_ops)
		return -ENODEV;

	count = handle->clk_ops->count_get(handle);
	if (count < 0) {
		dev_err(dev, "%pOFn: invalid clock output count\n", np);
		return -EINVAL;
	}

	clk_data = devm_kzalloc(dev, struct_size(clk_data, hws, count),
				GFP_KERNEL);
	if (!clk_data)
		return -ENOMEM;

	clk_data->num = count;
	hws = clk_data->hws;

	for (idx = 0; idx < count; idx++) {
		struct scmi_clk *sclk;

		sclk = devm_kzalloc(dev, sizeof(*sclk), GFP_KERNEL);
		if (!sclk)
			return -ENOMEM;

		sclk->info = handle->clk_ops->info_get(handle, idx);
		if (!sclk->info) {
			dev_dbg(dev, "invalid clock info for idx %d\n", idx);
			continue;
		}

		sclk->id = idx;
		sclk->handle = handle;

		err = scmi_clk_ops_init(dev, sclk);
		if (err) {
			dev_err(dev, "failed to register clock %d\n", idx);
			devm_kfree(dev, sclk);
			hws[idx] = NULL;
		} else {
			dev_dbg(dev, "Registered clock:%s\n", sclk->info->name);
			hws[idx] = &sclk->hw;
		}
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   clk_data);
}