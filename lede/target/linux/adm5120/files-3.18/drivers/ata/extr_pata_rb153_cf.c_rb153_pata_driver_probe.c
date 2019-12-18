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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct rb153_cf_info {int gpio_line; unsigned int irq; int /*<<< orphan*/  iobase; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ata_host {struct rb153_cf_info* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  RB153_CF_MAXPORTS ; 
 int ata_host_activate (struct ata_host*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ata_host* ata_host_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct rb153_cf_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int irq_to_gpio (unsigned int) ; 
 unsigned int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ata_host*) ; 
 int /*<<< orphan*/  rb153_pata_irq_handler ; 
 int /*<<< orphan*/  rb153_pata_setup_port (struct ata_host*) ; 
 int /*<<< orphan*/  rb153_pata_sht ; 

__attribute__((used)) static int rb153_pata_driver_probe(struct platform_device *pdev)
{
	unsigned int irq;
	int gpio;
	struct resource *res;
	struct ata_host *ah;
	struct rb153_cf_info *info;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no IOMEM resource found\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "no IRQ resource found\n");
		return -ENOENT;
	}

	gpio = irq_to_gpio(irq);
	if (gpio < 0) {
		dev_err(&pdev->dev, "no GPIO found for irq%d\n", irq);
		return -ENOENT;
	}

	ret = gpio_request(gpio, DRV_NAME);
	if (ret) {
		dev_err(&pdev->dev, "GPIO request failed\n");
		return ret;
	}

	ah = ata_host_alloc(&pdev->dev, RB153_CF_MAXPORTS);
	if (!ah)
		return -ENOMEM;

	platform_set_drvdata(pdev, ah);

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	ah->private_data = info;
	info->gpio_line = gpio;
	info->irq = irq;

	info->iobase = devm_ioremap_nocache(&pdev->dev, res->start,
				res->end - res->start + 1);
	if (!info->iobase)
		return -ENOMEM;

	ret = gpio_direction_input(gpio);
	if (ret) {
		dev_err(&pdev->dev, "unable to set GPIO direction, err=%d\n",
				ret);
		goto err_free_gpio;
	}

	rb153_pata_setup_port(ah);

	ret = ata_host_activate(ah, irq, rb153_pata_irq_handler,
				IRQF_TRIGGER_LOW, &rb153_pata_sht);
	if (ret)
		goto err_free_gpio;

	return 0;

err_free_gpio:
	gpio_free(gpio);

	return ret;
}