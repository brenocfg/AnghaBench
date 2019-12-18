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
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct gpio_extcon_data {scalar_t__ extcon_id; TYPE_1__ work; int /*<<< orphan*/  edev; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ EXTCON_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (struct device*,scalar_t__*) ; 
 int devm_extcon_dev_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct gpio_extcon_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_any_context_irq (struct device*,int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct gpio_extcon_data*) ; 
 int /*<<< orphan*/  gpio_extcon_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_irq_handler ; 
 scalar_t__ gpiod_is_active_low (int /*<<< orphan*/ ) ; 
 int gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_extcon_data*) ; 

__attribute__((used)) static int gpio_extcon_probe(struct platform_device *pdev)
{
	struct gpio_extcon_data *data;
	struct device *dev = &pdev->dev;
	unsigned long irq_flags;
	int irq;
	int ret;

	data = devm_kzalloc(dev, sizeof(struct gpio_extcon_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	/*
	 * FIXME: extcon_id represents the unique identifier of external
	 * connectors such as EXTCON_USB, EXTCON_DISP_HDMI and so on. extcon_id
	 * is necessary to register the extcon device. But, it's not yet
	 * developed to get the extcon id from device-tree or others.
	 * On later, it have to be solved.
	 */
	if (data->extcon_id > EXTCON_NONE)
		return -EINVAL;

	data->gpiod = devm_gpiod_get(dev, "extcon", GPIOD_IN);
	if (IS_ERR(data->gpiod))
		return PTR_ERR(data->gpiod);
	irq = gpiod_to_irq(data->gpiod);
	if (irq <= 0)
		return irq;

	/*
	 * It is unlikely that this is an acknowledged interrupt that goes
	 * away after handling, what we are looking for are falling edges
	 * if the signal is active low, and rising edges if the signal is
	 * active high.
	 */
	if (gpiod_is_active_low(data->gpiod))
		irq_flags = IRQF_TRIGGER_FALLING;
	else
		irq_flags = IRQF_TRIGGER_RISING;

	/* Allocate the memory of extcon devie and register extcon device */
	data->edev = devm_extcon_dev_allocate(dev, &data->extcon_id);
	if (IS_ERR(data->edev)) {
		dev_err(dev, "failed to allocate extcon device\n");
		return -ENOMEM;
	}

	ret = devm_extcon_dev_register(dev, data->edev);
	if (ret < 0)
		return ret;

	INIT_DELAYED_WORK(&data->work, gpio_extcon_work);

	/*
	 * Request the interrupt of gpio to detect whether external connector
	 * is attached or detached.
	 */
	ret = devm_request_any_context_irq(dev, irq,
					gpio_irq_handler, irq_flags,
					pdev->name, data);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, data);
	/* Perform initial detection */
	gpio_extcon_work(&data->work.work);

	return 0;
}