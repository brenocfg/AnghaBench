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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int dummy; } ;
struct gpio_chip {int ngpio; int /*<<< orphan*/  of_node; } ;
struct bcm_kona_gpio_bank {int id; scalar_t__ irq; struct bcm_kona_gpio* kona_gpio; } ;
struct bcm_kona_gpio {int num_bank; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  lock; struct bcm_kona_gpio_bank* banks; int /*<<< orphan*/  reg_base; struct platform_device* pdev; struct gpio_chip gpio_chip; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIO_MAX_BANK_NUM ; 
 int GPIO_PER_BANK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_kona_gpio_irq_handler ; 
 int /*<<< orphan*/  bcm_kona_gpio_of_match ; 
 int /*<<< orphan*/  bcm_kona_gpio_reset (struct bcm_kona_gpio*) ; 
 int /*<<< orphan*/  bcm_kona_irq_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,struct bcm_kona_gpio*) ; 
 struct bcm_kona_gpio_bank* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct bcm_kona_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct bcm_kona_gpio*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (scalar_t__,int /*<<< orphan*/ ,struct bcm_kona_gpio_bank*) ; 
 int of_irq_count (int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_kona_gpio*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 struct gpio_chip template_chip ; 

__attribute__((used)) static int bcm_kona_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *match;
	struct bcm_kona_gpio_bank *bank;
	struct bcm_kona_gpio *kona_gpio;
	struct gpio_chip *chip;
	int ret;
	int i;

	match = of_match_device(bcm_kona_gpio_of_match, dev);
	if (!match) {
		dev_err(dev, "Failed to find gpio controller\n");
		return -ENODEV;
	}

	kona_gpio = devm_kzalloc(dev, sizeof(*kona_gpio), GFP_KERNEL);
	if (!kona_gpio)
		return -ENOMEM;

	kona_gpio->gpio_chip = template_chip;
	chip = &kona_gpio->gpio_chip;
	kona_gpio->num_bank = of_irq_count(dev->of_node);
	if (kona_gpio->num_bank == 0) {
		dev_err(dev, "Couldn't determine # GPIO banks\n");
		return -ENOENT;
	}
	if (kona_gpio->num_bank > GPIO_MAX_BANK_NUM) {
		dev_err(dev, "Too many GPIO banks configured (max=%d)\n",
			GPIO_MAX_BANK_NUM);
		return -ENXIO;
	}
	kona_gpio->banks = devm_kcalloc(dev,
					kona_gpio->num_bank,
					sizeof(*kona_gpio->banks),
					GFP_KERNEL);
	if (!kona_gpio->banks)
		return -ENOMEM;

	kona_gpio->pdev = pdev;
	platform_set_drvdata(pdev, kona_gpio);
	chip->of_node = dev->of_node;
	chip->ngpio = kona_gpio->num_bank * GPIO_PER_BANK;

	kona_gpio->irq_domain = irq_domain_add_linear(dev->of_node,
						      chip->ngpio,
						      &bcm_kona_irq_ops,
						      kona_gpio);
	if (!kona_gpio->irq_domain) {
		dev_err(dev, "Couldn't allocate IRQ domain\n");
		return -ENXIO;
	}

	kona_gpio->reg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(kona_gpio->reg_base)) {
		ret = -ENXIO;
		goto err_irq_domain;
	}

	for (i = 0; i < kona_gpio->num_bank; i++) {
		bank = &kona_gpio->banks[i];
		bank->id = i;
		bank->irq = platform_get_irq(pdev, i);
		bank->kona_gpio = kona_gpio;
		if (bank->irq < 0) {
			dev_err(dev, "Couldn't get IRQ for bank %d", i);
			ret = -ENOENT;
			goto err_irq_domain;
		}
	}

	dev_info(&pdev->dev, "Setting up Kona GPIO\n");

	bcm_kona_gpio_reset(kona_gpio);

	ret = devm_gpiochip_add_data(dev, chip, kona_gpio);
	if (ret < 0) {
		dev_err(dev, "Couldn't add GPIO chip -- %d\n", ret);
		goto err_irq_domain;
	}
	for (i = 0; i < kona_gpio->num_bank; i++) {
		bank = &kona_gpio->banks[i];
		irq_set_chained_handler_and_data(bank->irq,
						 bcm_kona_gpio_irq_handler,
						 bank);
	}

	raw_spin_lock_init(&kona_gpio->lock);

	return 0;

err_irq_domain:
	irq_domain_remove(kona_gpio->irq_domain);

	return ret;
}