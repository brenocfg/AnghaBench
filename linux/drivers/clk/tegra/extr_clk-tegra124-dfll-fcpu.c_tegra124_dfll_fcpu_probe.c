#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rail_alignment {int dummy; } ;
struct tegra_dfll_soc_data {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  cvb; int /*<<< orphan*/  dev; struct rail_alignment alignment; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct dfll_fcpu_data {int cpu_max_freq_table_size; int /*<<< orphan*/  cpu_cvb_tables_size; int /*<<< orphan*/  cpu_cvb_tables; int /*<<< orphan*/ * cpu_max_freq_table; } ;
struct TYPE_7__ {int cpu_process_id; int cpu_speedo_id; int cpu_speedo_value; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct tegra_dfll_soc_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alignment_from_dt (TYPE_2__*,struct rail_alignment*) ; 
 int get_alignment_from_regulator (TYPE_2__*,struct rail_alignment*) ; 
 int /*<<< orphan*/  get_cpu_device (int /*<<< orphan*/ ) ; 
 struct dfll_fcpu_data* of_device_get_match_data (TYPE_2__*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tegra_cvb_add_opp_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rail_alignment*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_cvb_remove_opp_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tegra_dfll_register (struct platform_device*,struct tegra_dfll_soc_data*) ; 
 TYPE_1__ tegra_sku_info ; 

__attribute__((used)) static int tegra124_dfll_fcpu_probe(struct platform_device *pdev)
{
	int process_id, speedo_id, speedo_value, err;
	struct tegra_dfll_soc_data *soc;
	const struct dfll_fcpu_data *fcpu_data;
	struct rail_alignment align;

	fcpu_data = of_device_get_match_data(&pdev->dev);
	if (!fcpu_data)
		return -ENODEV;

	process_id = tegra_sku_info.cpu_process_id;
	speedo_id = tegra_sku_info.cpu_speedo_id;
	speedo_value = tegra_sku_info.cpu_speedo_value;

	if (speedo_id >= fcpu_data->cpu_max_freq_table_size) {
		dev_err(&pdev->dev, "unknown max CPU freq for speedo_id=%d\n",
			speedo_id);
		return -ENODEV;
	}

	soc = devm_kzalloc(&pdev->dev, sizeof(*soc), GFP_KERNEL);
	if (!soc)
		return -ENOMEM;

	soc->dev = get_cpu_device(0);
	if (!soc->dev) {
		dev_err(&pdev->dev, "no CPU0 device\n");
		return -ENODEV;
	}

	if (of_property_read_bool(pdev->dev.of_node, "nvidia,pwm-to-pmic")) {
		get_alignment_from_dt(&pdev->dev, &align);
	} else {
		err = get_alignment_from_regulator(&pdev->dev, &align);
		if (err)
			return err;
	}

	soc->max_freq = fcpu_data->cpu_max_freq_table[speedo_id];

	soc->cvb = tegra_cvb_add_opp_table(soc->dev, fcpu_data->cpu_cvb_tables,
					   fcpu_data->cpu_cvb_tables_size,
					   &align, process_id, speedo_id,
					   speedo_value, soc->max_freq);
	soc->alignment = align;

	if (IS_ERR(soc->cvb)) {
		dev_err(&pdev->dev, "couldn't add OPP table: %ld\n",
			PTR_ERR(soc->cvb));
		return PTR_ERR(soc->cvb);
	}

	err = tegra_dfll_register(pdev, soc);
	if (err < 0) {
		tegra_cvb_remove_opp_table(soc->dev, soc->cvb, soc->max_freq);
		return err;
	}

	return 0;
}