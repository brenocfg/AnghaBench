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
struct rb91x_nand_info {int /*<<< orphan*/  gpio_rdy; int /*<<< orphan*/  dev; int /*<<< orphan*/  gpio_read; int /*<<< orphan*/  gpio_ale; int /*<<< orphan*/  gpio_cle; int /*<<< orphan*/  gpio_nrw; int /*<<< orphan*/  gpio_nce; int /*<<< orphan*/  gpio_nle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int devm_gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rb91x_nand_gpio_init(struct rb91x_nand_info *info)
{
	int ret;

	/*
	 * Ensure that the LATCH is disabled before initializing
	 * control lines.
	 */
	ret = devm_gpio_request_one(info->dev, info->gpio_nle,
				    GPIOF_OUT_INIT_HIGH, "LATCH enable");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(info->dev, info->gpio_nce,
				    GPIOF_OUT_INIT_HIGH, "NAND nCE");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(info->dev, info->gpio_nrw,
				    GPIOF_OUT_INIT_HIGH, "NAND nRW");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(info->dev, info->gpio_cle,
				    GPIOF_OUT_INIT_LOW, "NAND CLE");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(info->dev, info->gpio_ale,
				    GPIOF_OUT_INIT_LOW, "NAND ALE");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(info->dev, info->gpio_read,
				    GPIOF_OUT_INIT_LOW, "NAND READ");
	if (ret)
		return ret;

	ret = devm_gpio_request_one(info->dev, info->gpio_rdy,
				    GPIOF_IN, "NAND RDY");
	return ret;
}