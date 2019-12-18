#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {char* label; int base; int ngpio; int can_sleep; int /*<<< orphan*/  set_config; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  owner; struct device* parent; } ;
struct dln2_gpio {TYPE_1__ gpio; struct platform_device* pdev; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_GPIO_CONDITION_MET_EV ; 
 int DLN2_GPIO_MAX_PINS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct dln2_gpio*) ; 
 struct dln2_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dln2_gpio_direction_input ; 
 int /*<<< orphan*/  dln2_gpio_direction_output ; 
 int /*<<< orphan*/  dln2_gpio_event ; 
 int /*<<< orphan*/  dln2_gpio_free ; 
 int /*<<< orphan*/  dln2_gpio_get ; 
 int /*<<< orphan*/  dln2_gpio_get_direction ; 
 int dln2_gpio_get_pin_count (struct platform_device*) ; 
 int /*<<< orphan*/  dln2_gpio_irqchip ; 
 int /*<<< orphan*/  dln2_gpio_request ; 
 int /*<<< orphan*/  dln2_gpio_set ; 
 int /*<<< orphan*/  dln2_gpio_set_config ; 
 int dln2_register_event_cb (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiochip_irqchip_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dln2_gpio*) ; 

__attribute__((used)) static int dln2_gpio_probe(struct platform_device *pdev)
{
	struct dln2_gpio *dln2;
	struct device *dev = &pdev->dev;
	int pins;
	int ret;

	pins = dln2_gpio_get_pin_count(pdev);
	if (pins < 0) {
		dev_err(dev, "failed to get pin count: %d\n", pins);
		return pins;
	}
	if (pins > DLN2_GPIO_MAX_PINS) {
		pins = DLN2_GPIO_MAX_PINS;
		dev_warn(dev, "clamping pins to %d\n", DLN2_GPIO_MAX_PINS);
	}

	dln2 = devm_kzalloc(&pdev->dev, sizeof(*dln2), GFP_KERNEL);
	if (!dln2)
		return -ENOMEM;

	mutex_init(&dln2->irq_lock);

	dln2->pdev = pdev;

	dln2->gpio.label = "dln2";
	dln2->gpio.parent = dev;
	dln2->gpio.owner = THIS_MODULE;
	dln2->gpio.base = -1;
	dln2->gpio.ngpio = pins;
	dln2->gpio.can_sleep = true;
	dln2->gpio.set = dln2_gpio_set;
	dln2->gpio.get = dln2_gpio_get;
	dln2->gpio.request = dln2_gpio_request;
	dln2->gpio.free = dln2_gpio_free;
	dln2->gpio.get_direction = dln2_gpio_get_direction;
	dln2->gpio.direction_input = dln2_gpio_direction_input;
	dln2->gpio.direction_output = dln2_gpio_direction_output;
	dln2->gpio.set_config = dln2_gpio_set_config;

	platform_set_drvdata(pdev, dln2);

	ret = devm_gpiochip_add_data(dev, &dln2->gpio, dln2);
	if (ret < 0) {
		dev_err(dev, "failed to add gpio chip: %d\n", ret);
		return ret;
	}

	ret = gpiochip_irqchip_add(&dln2->gpio, &dln2_gpio_irqchip, 0,
				   handle_simple_irq, IRQ_TYPE_NONE);
	if (ret < 0) {
		dev_err(dev, "failed to add irq chip: %d\n", ret);
		return ret;
	}

	ret = dln2_register_event_cb(pdev, DLN2_GPIO_CONDITION_MET_EV,
				     dln2_gpio_event);
	if (ret) {
		dev_err(dev, "failed to register event cb: %d\n", ret);
		return ret;
	}

	return 0;
}