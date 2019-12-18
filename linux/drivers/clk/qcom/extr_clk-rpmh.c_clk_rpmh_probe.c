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
typedef  scalar_t__ u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk_rpmh_desc {int num_clks; struct clk_hw** clks; } ;
struct clk_rpmh {unsigned long long unit; int /*<<< orphan*/ * dev; int /*<<< orphan*/  res_addr; int /*<<< orphan*/  res_name; } ;
struct clk_hw {TYPE_1__* init; } ;
struct bcm_db {int /*<<< orphan*/  unit; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct bcm_db const*) ; 
 int PTR_ERR (struct bcm_db const*) ; 
 scalar_t__ cmd_db_read_addr (int /*<<< orphan*/ ) ; 
 struct bcm_db* cmd_db_read_aux_data (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int devm_of_clk_add_hw_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_rpmh_hw_get ; 
 struct clk_rpmh_desc* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct clk_rpmh* to_clk_rpmh (struct clk_hw*) ; 

__attribute__((used)) static int clk_rpmh_probe(struct platform_device *pdev)
{
	struct clk_hw **hw_clks;
	struct clk_rpmh *rpmh_clk;
	const struct clk_rpmh_desc *desc;
	int ret, i;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		return -ENODEV;

	hw_clks = desc->clks;

	for (i = 0; i < desc->num_clks; i++) {
		const char *name = hw_clks[i]->init->name;
		u32 res_addr;
		size_t aux_data_len;
		const struct bcm_db *data;

		rpmh_clk = to_clk_rpmh(hw_clks[i]);
		res_addr = cmd_db_read_addr(rpmh_clk->res_name);
		if (!res_addr) {
			dev_err(&pdev->dev, "missing RPMh resource address for %s\n",
				rpmh_clk->res_name);
			return -ENODEV;
		}

		data = cmd_db_read_aux_data(rpmh_clk->res_name, &aux_data_len);
		if (IS_ERR(data)) {
			ret = PTR_ERR(data);
			dev_err(&pdev->dev,
				"error reading RPMh aux data for %s (%d)\n",
				rpmh_clk->res_name, ret);
			return ret;
		}

		/* Convert unit from Khz to Hz */
		if (aux_data_len == sizeof(*data))
			rpmh_clk->unit = le32_to_cpu(data->unit) * 1000ULL;

		rpmh_clk->res_addr += res_addr;
		rpmh_clk->dev = &pdev->dev;

		ret = devm_clk_hw_register(&pdev->dev, hw_clks[i]);
		if (ret) {
			dev_err(&pdev->dev, "failed to register %s\n", name);
			return ret;
		}
	}

	/* typecast to silence compiler warning */
	ret = devm_of_clk_add_hw_provider(&pdev->dev, of_clk_rpmh_hw_get,
					  (void *)desc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to add clock provider\n");
		return ret;
	}

	dev_dbg(&pdev->dev, "Registered RPMh clocks\n");

	return 0;
}