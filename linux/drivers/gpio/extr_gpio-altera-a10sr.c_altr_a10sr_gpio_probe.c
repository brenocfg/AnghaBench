#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct altr_a10sr_gpio {TYPE_3__ gp; int /*<<< orphan*/  regmap; } ;
struct altr_a10sr {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__ altr_a10sr_gc ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct altr_a10sr* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_1__*,TYPE_3__*,struct altr_a10sr_gpio*) ; 
 struct altr_a10sr_gpio* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct altr_a10sr_gpio*) ; 

__attribute__((used)) static int altr_a10sr_gpio_probe(struct platform_device *pdev)
{
	struct altr_a10sr_gpio *gpio;
	int ret;
	struct altr_a10sr *a10sr = dev_get_drvdata(pdev->dev.parent);

	gpio = devm_kzalloc(&pdev->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	gpio->regmap = a10sr->regmap;

	gpio->gp = altr_a10sr_gc;
	gpio->gp.parent = pdev->dev.parent;
	gpio->gp.of_node = pdev->dev.of_node;

	ret = devm_gpiochip_add_data(&pdev->dev, &gpio->gp, gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, gpio);

	return 0;
}