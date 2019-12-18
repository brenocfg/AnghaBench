#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tegra_dfll_soc_data {int dummy; } ;
struct tegra_dfll {TYPE_1__* dev; void* lut_base; void* i2c_controller_base; void* i2c_base; void* base; int /*<<< orphan*/  pmu_if; int /*<<< orphan*/  vdd_reg; int /*<<< orphan*/  dvco_rst; struct tegra_dfll_soc_data* soc; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEGRA_DFLL_PMU_I2C ; 
 int /*<<< orphan*/  TEGRA_DFLL_PMU_PWM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_dfll* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get (TYPE_1__*,char*) ; 
 int dfll_build_lut (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_debug_init (struct tegra_dfll*) ; 
 int dfll_fetch_common_params (struct tegra_dfll*) ; 
 int dfll_fetch_i2c_params (struct tegra_dfll*) ; 
 int dfll_fetch_pwm_params (struct tegra_dfll*) ; 
 int dfll_init (struct tegra_dfll*) ; 
 int dfll_init_clks (struct tegra_dfll*) ; 
 int dfll_register_clk (struct tegra_dfll*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_dfll*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

int tegra_dfll_register(struct platform_device *pdev,
			struct tegra_dfll_soc_data *soc)
{
	struct resource *mem;
	struct tegra_dfll *td;
	int ret;

	if (!soc) {
		dev_err(&pdev->dev, "no tegra_dfll_soc_data provided\n");
		return -EINVAL;
	}

	td = devm_kzalloc(&pdev->dev, sizeof(*td), GFP_KERNEL);
	if (!td)
		return -ENOMEM;
	td->dev = &pdev->dev;
	platform_set_drvdata(pdev, td);

	td->soc = soc;

	td->dvco_rst = devm_reset_control_get(td->dev, "dvco");
	if (IS_ERR(td->dvco_rst)) {
		dev_err(td->dev, "couldn't get dvco reset\n");
		return PTR_ERR(td->dvco_rst);
	}

	ret = dfll_fetch_common_params(td);
	if (ret) {
		dev_err(td->dev, "couldn't parse device tree parameters\n");
		return ret;
	}

	if (of_property_read_bool(td->dev->of_node, "nvidia,pwm-to-pmic")) {
		td->pmu_if = TEGRA_DFLL_PMU_PWM;
		ret = dfll_fetch_pwm_params(td);
	} else  {
		td->vdd_reg = devm_regulator_get(td->dev, "vdd-cpu");
		if (IS_ERR(td->vdd_reg)) {
			dev_err(td->dev, "couldn't get vdd_cpu regulator\n");
			return PTR_ERR(td->vdd_reg);
		}
		td->pmu_if = TEGRA_DFLL_PMU_I2C;
		ret = dfll_fetch_i2c_params(td);
	}
	if (ret)
		return ret;

	ret = dfll_build_lut(td);
	if (ret) {
		dev_err(td->dev, "couldn't build LUT\n");
		return ret;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem) {
		dev_err(td->dev, "no control register resource\n");
		return -ENODEV;
	}

	td->base = devm_ioremap(td->dev, mem->start, resource_size(mem));
	if (!td->base) {
		dev_err(td->dev, "couldn't ioremap DFLL control registers\n");
		return -ENODEV;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!mem) {
		dev_err(td->dev, "no i2c_base resource\n");
		return -ENODEV;
	}

	td->i2c_base = devm_ioremap(td->dev, mem->start, resource_size(mem));
	if (!td->i2c_base) {
		dev_err(td->dev, "couldn't ioremap i2c_base resource\n");
		return -ENODEV;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!mem) {
		dev_err(td->dev, "no i2c_controller_base resource\n");
		return -ENODEV;
	}

	td->i2c_controller_base = devm_ioremap(td->dev, mem->start,
					       resource_size(mem));
	if (!td->i2c_controller_base) {
		dev_err(td->dev,
			"couldn't ioremap i2c_controller_base resource\n");
		return -ENODEV;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 3);
	if (!mem) {
		dev_err(td->dev, "no lut_base resource\n");
		return -ENODEV;
	}

	td->lut_base = devm_ioremap(td->dev, mem->start, resource_size(mem));
	if (!td->lut_base) {
		dev_err(td->dev,
			"couldn't ioremap lut_base resource\n");
		return -ENODEV;
	}

	ret = dfll_init_clks(td);
	if (ret) {
		dev_err(&pdev->dev, "DFLL clock init error\n");
		return ret;
	}

	/* Enable the clocks and set the device up */
	ret = dfll_init(td);
	if (ret)
		return ret;

	ret = dfll_register_clk(td);
	if (ret) {
		dev_err(&pdev->dev, "DFLL clk registration failed\n");
		return ret;
	}

	dfll_debug_init(td);

	return 0;
}