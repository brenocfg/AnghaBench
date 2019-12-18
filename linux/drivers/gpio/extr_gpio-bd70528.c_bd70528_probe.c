#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rohm_regmap_dev {int /*<<< orphan*/  regmap; } ;
struct TYPE_8__ {TYPE_5__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_9__ {char* label; int can_sleep; int ngpio; int base; int /*<<< orphan*/  of_node; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  set_config; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  owner; TYPE_5__* parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  regmap; TYPE_2__* dev; } ;
struct bd70528_gpio {TYPE_4__ gpio; TYPE_1__ chip; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bd70528_direction_input ; 
 int /*<<< orphan*/  bd70528_direction_output ; 
 int /*<<< orphan*/  bd70528_get_direction ; 
 int /*<<< orphan*/  bd70528_gpio_get ; 
 int /*<<< orphan*/  bd70528_gpio_set ; 
 int /*<<< orphan*/  bd70528_gpio_set_config ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct rohm_regmap_dev* dev_get_drvdata (TYPE_5__*) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_4__*,struct bd70528_gpio*) ; 
 struct bd70528_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bd70528_probe(struct platform_device *pdev)
{
	struct bd70528_gpio *bdgpio;
	struct rohm_regmap_dev *bd70528;
	int ret;

	bd70528 = dev_get_drvdata(pdev->dev.parent);
	if (!bd70528) {
		dev_err(&pdev->dev, "No MFD driver data\n");
		return -EINVAL;
	}

	bdgpio = devm_kzalloc(&pdev->dev, sizeof(*bdgpio),
			      GFP_KERNEL);
	if (!bdgpio)
		return -ENOMEM;
	bdgpio->chip.dev = &pdev->dev;
	bdgpio->gpio.parent = pdev->dev.parent;
	bdgpio->gpio.label = "bd70528-gpio";
	bdgpio->gpio.owner = THIS_MODULE;
	bdgpio->gpio.get_direction = bd70528_get_direction;
	bdgpio->gpio.direction_input = bd70528_direction_input;
	bdgpio->gpio.direction_output = bd70528_direction_output;
	bdgpio->gpio.set_config = bd70528_gpio_set_config;
	bdgpio->gpio.can_sleep = true;
	bdgpio->gpio.get = bd70528_gpio_get;
	bdgpio->gpio.set = bd70528_gpio_set;
	bdgpio->gpio.ngpio = 4;
	bdgpio->gpio.base = -1;
#ifdef CONFIG_OF_GPIO
	bdgpio->gpio.of_node = pdev->dev.parent->of_node;
#endif
	bdgpio->chip.regmap = bd70528->regmap;

	ret = devm_gpiochip_add_data(&pdev->dev, &bdgpio->gpio,
				     bdgpio);
	if (ret)
		dev_err(&pdev->dev, "gpio_init: Failed to add bd70528-gpio\n");

	return ret;
}