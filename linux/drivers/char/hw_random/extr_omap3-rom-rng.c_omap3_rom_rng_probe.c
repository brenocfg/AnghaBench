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
struct TYPE_2__ {int /*<<< orphan*/  platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int hwrng_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_work ; 
 int /*<<< orphan*/  omap3_rom_rng_call ; 
 int /*<<< orphan*/  omap3_rom_rng_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3_rom_rng_ops ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rng_clk ; 

__attribute__((used)) static int omap3_rom_rng_probe(struct platform_device *pdev)
{
	int ret = 0;

	pr_info("initializing\n");

	omap3_rom_rng_call = pdev->dev.platform_data;
	if (!omap3_rom_rng_call) {
		pr_err("omap3_rom_rng_call is NULL\n");
		return -EINVAL;
	}

	INIT_DELAYED_WORK(&idle_work, omap3_rom_rng_idle);
	rng_clk = devm_clk_get(&pdev->dev, "ick");
	if (IS_ERR(rng_clk)) {
		pr_err("unable to get RNG clock\n");
		return PTR_ERR(rng_clk);
	}

	/* Leave the RNG in reset state. */
	ret = clk_prepare_enable(rng_clk);
	if (ret)
		return ret;
	omap3_rom_rng_idle(0);

	return hwrng_register(&omap3_rom_rng_ops);
}