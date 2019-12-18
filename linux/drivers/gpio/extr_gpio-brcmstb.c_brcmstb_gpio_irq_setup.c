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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_unmask; void* irq_mask; void* irq_disable; int /*<<< orphan*/  name; } ;
struct brcmstb_gpio_priv {scalar_t__ parent_wake_irq; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  parent_irq; TYPE_1__ irq_chip; int /*<<< orphan*/  num_gpios; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_DISABLE_UNLAZY ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_ack ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_domain_ops ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_handler ; 
 void* brcmstb_gpio_irq_mask ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_set_type ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_set_wake ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_unmask ; 
 int /*<<< orphan*/  brcmstb_gpio_wake_irq_handler ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 int /*<<< orphan*/  device_wakeup_enable (struct device*) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct brcmstb_gpio_priv*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct brcmstb_gpio_priv*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmstb_gpio_priv*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 

__attribute__((used)) static int brcmstb_gpio_irq_setup(struct platform_device *pdev,
		struct brcmstb_gpio_priv *priv)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int err;

	priv->irq_domain =
		irq_domain_add_linear(np, priv->num_gpios,
				      &brcmstb_gpio_irq_domain_ops,
				      priv);
	if (!priv->irq_domain) {
		dev_err(dev, "Couldn't allocate IRQ domain\n");
		return -ENXIO;
	}

	if (of_property_read_bool(np, "wakeup-source")) {
		priv->parent_wake_irq = platform_get_irq(pdev, 1);
		if (priv->parent_wake_irq < 0) {
			priv->parent_wake_irq = 0;
			dev_warn(dev,
				"Couldn't get wake IRQ - GPIOs will not be able to wake from sleep");
		} else {
			/*
			 * Set wakeup capability so we can process boot-time
			 * "wakeups" (e.g., from S5 cold boot)
			 */
			device_set_wakeup_capable(dev, true);
			device_wakeup_enable(dev);
			err = devm_request_irq(dev, priv->parent_wake_irq,
					       brcmstb_gpio_wake_irq_handler,
					       IRQF_SHARED,
					       "brcmstb-gpio-wake", priv);

			if (err < 0) {
				dev_err(dev, "Couldn't request wake IRQ");
				goto out_free_domain;
			}
		}
	}

	priv->irq_chip.name = dev_name(dev);
	priv->irq_chip.irq_disable = brcmstb_gpio_irq_mask;
	priv->irq_chip.irq_mask = brcmstb_gpio_irq_mask;
	priv->irq_chip.irq_unmask = brcmstb_gpio_irq_unmask;
	priv->irq_chip.irq_ack = brcmstb_gpio_irq_ack;
	priv->irq_chip.irq_set_type = brcmstb_gpio_irq_set_type;

	if (priv->parent_wake_irq)
		priv->irq_chip.irq_set_wake = brcmstb_gpio_irq_set_wake;

	irq_set_chained_handler_and_data(priv->parent_irq,
					 brcmstb_gpio_irq_handler, priv);
	irq_set_status_flags(priv->parent_irq, IRQ_DISABLE_UNLAZY);

	return 0;

out_free_domain:
	irq_domain_remove(priv->irq_domain);

	return err;
}