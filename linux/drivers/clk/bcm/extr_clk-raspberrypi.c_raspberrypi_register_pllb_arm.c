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
struct raspberrypi_clk {int /*<<< orphan*/  pllb_arm; int /*<<< orphan*/  dev; int /*<<< orphan*/  pllb_arm_lookup; } ;

/* Variables and functions */
 int CLK_GET_RATE_NOCACHE ; 
 int CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_register_fixed_factor (int /*<<< orphan*/ ,char*,char*,int,int,int) ; 
 int /*<<< orphan*/  clk_hw_unregister_fixed_factor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_hw_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int raspberrypi_register_pllb_arm(struct raspberrypi_clk *rpi)
{
	rpi->pllb_arm = clk_hw_register_fixed_factor(rpi->dev,
				"pllb_arm", "pllb",
				CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE,
				1, 2);
	if (IS_ERR(rpi->pllb_arm)) {
		dev_err(rpi->dev, "Failed to initialize pllb_arm\n");
		return PTR_ERR(rpi->pllb_arm);
	}

	rpi->pllb_arm_lookup = clkdev_hw_create(rpi->pllb_arm, NULL, "cpu0");
	if (!rpi->pllb_arm_lookup) {
		dev_err(rpi->dev, "Failed to initialize pllb_arm_lookup\n");
		clk_hw_unregister_fixed_factor(rpi->pllb_arm);
		return -ENOMEM;
	}

	return 0;
}