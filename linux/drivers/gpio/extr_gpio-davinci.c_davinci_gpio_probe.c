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
struct device {int /*<<< orphan*/  of_node; struct davinci_gpio_platform_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct davinci_gpio_platform_data {unsigned int ngpio; int gpio_unbanked; int base; scalar_t__ no_auto_base; } ;
struct TYPE_2__ {unsigned int ngpio; int base; int of_gpio_n_cells; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  label; } ;
struct davinci_gpio_controller {int* irqs; TYPE_1__ chip; scalar_t__* regs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int ARCH_NR_GPIOS ; 
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  davinci_direction_in ; 
 int /*<<< orphan*/  davinci_direction_out ; 
 int /*<<< orphan*/  davinci_gpio_get ; 
 struct davinci_gpio_platform_data* davinci_gpio_get_pdata (struct platform_device*) ; 
 int davinci_gpio_irq_setup (struct platform_device*) ; 
 int /*<<< orphan*/  davinci_gpio_set ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct davinci_gpio_controller*) ; 
 struct davinci_gpio_controller* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_base ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__* offset_array ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct davinci_gpio_controller*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_gpio_probe(struct platform_device *pdev)
{
	int bank, i, ret = 0;
	unsigned int ngpio, nbank, nirq;
	struct davinci_gpio_controller *chips;
	struct davinci_gpio_platform_data *pdata;
	struct device *dev = &pdev->dev;

	pdata = davinci_gpio_get_pdata(pdev);
	if (!pdata) {
		dev_err(dev, "No platform data found\n");
		return -EINVAL;
	}

	dev->platform_data = pdata;

	/*
	 * The gpio banks conceptually expose a segmented bitmap,
	 * and "ngpio" is one more than the largest zero-based
	 * bit index that's valid.
	 */
	ngpio = pdata->ngpio;
	if (ngpio == 0) {
		dev_err(dev, "How many GPIOs?\n");
		return -EINVAL;
	}

	if (WARN_ON(ARCH_NR_GPIOS < ngpio))
		ngpio = ARCH_NR_GPIOS;

	/*
	 * If there are unbanked interrupts then the number of
	 * interrupts is equal to number of gpios else all are banked so
	 * number of interrupts is equal to number of banks(each with 16 gpios)
	 */
	if (pdata->gpio_unbanked)
		nirq = pdata->gpio_unbanked;
	else
		nirq = DIV_ROUND_UP(ngpio, 16);

	chips = devm_kzalloc(dev, sizeof(*chips), GFP_KERNEL);
	if (!chips)
		return -ENOMEM;

	gpio_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(gpio_base))
		return PTR_ERR(gpio_base);

	for (i = 0; i < nirq; i++) {
		chips->irqs[i] = platform_get_irq(pdev, i);
		if (chips->irqs[i] < 0) {
			if (chips->irqs[i] != -EPROBE_DEFER)
				dev_info(dev, "IRQ not populated, err = %d\n",
					 chips->irqs[i]);
			return chips->irqs[i];
		}
	}

	chips->chip.label = dev_name(dev);

	chips->chip.direction_input = davinci_direction_in;
	chips->chip.get = davinci_gpio_get;
	chips->chip.direction_output = davinci_direction_out;
	chips->chip.set = davinci_gpio_set;

	chips->chip.ngpio = ngpio;
	chips->chip.base = pdata->no_auto_base ? pdata->base : -1;

#ifdef CONFIG_OF_GPIO
	chips->chip.of_gpio_n_cells = 2;
	chips->chip.parent = dev;
	chips->chip.of_node = dev->of_node;

	if (of_property_read_bool(dev->of_node, "gpio-ranges")) {
		chips->chip.request = gpiochip_generic_request;
		chips->chip.free = gpiochip_generic_free;
	}
#endif
	spin_lock_init(&chips->lock);

	nbank = DIV_ROUND_UP(ngpio, 32);
	for (bank = 0; bank < nbank; bank++)
		chips->regs[bank] = gpio_base + offset_array[bank];

	ret = devm_gpiochip_add_data(dev, &chips->chip, chips);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, chips);
	ret = davinci_gpio_irq_setup(pdev);
	if (ret)
		return ret;

	return 0;
}