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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_keys_platform_data {int nbuttons; struct gpio_keys_button* buttons; } ;
struct gpio_keys_button_dev {struct gpio_keys_button_data* data; struct gpio_keys_platform_data* pdata; } ;
struct gpio_keys_button_data {TYPE_1__* b; } ;
struct gpio_keys_button {scalar_t__ irq; int /*<<< orphan*/  gpio; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ EV_SW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  button_handle_irq ; 
 int /*<<< orphan*/  button_hotplug_event (struct gpio_keys_button_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct gpio_keys_button_data*) ; 
 int /*<<< orphan*/  gpio_button_get_value (struct gpio_keys_button_data*) ; 
 int gpio_keys_button_probe (struct platform_device*,struct gpio_keys_button_dev**,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_keys_probe(struct platform_device *pdev)
{
	struct gpio_keys_platform_data *pdata;
	struct gpio_keys_button_dev *bdev;
	int ret, i;


	ret = gpio_keys_button_probe(pdev, &bdev, 0);

	if (ret)
		return ret;

	pdata = bdev->pdata;
	for (i = 0; i < pdata->nbuttons; i++) {
		struct gpio_keys_button *button = &pdata->buttons[i];
		struct gpio_keys_button_data *bdata = &bdev->data[i];

		if (!button->irq)
			button->irq = gpio_to_irq(button->gpio);
		if (button->irq < 0) {
			dev_err(&pdev->dev, "failed to get irq for gpio:%d\n", button->gpio);
			continue;
		}

		ret = devm_request_threaded_irq(&pdev->dev, button->irq, NULL, button_handle_irq,
						IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
						dev_name(&pdev->dev), bdata);
		if (ret < 0)
			dev_err(&pdev->dev, "failed to request irq:%d for gpio:%d\n", button->irq, button->gpio);
		else
			dev_dbg(&pdev->dev, "gpio:%d has irq:%d\n", button->gpio, button->irq);

		if (bdata->b->type == EV_SW)
			button_hotplug_event(bdata, EV_SW, gpio_button_get_value(bdata));
	}

	return 0;
}