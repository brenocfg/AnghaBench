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
struct resource {int /*<<< orphan*/  start; } ;
struct rb532_cf_info {int irq; int /*<<< orphan*/  iobase; struct gpio_desc* gpio_line; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;
struct ata_host {struct rb532_cf_info* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  RB500_CF_MAXPORTS ; 
 int ata_host_activate (struct ata_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ata_host* ata_host_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct gpio_desc* devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rb532_cf_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (struct gpio_desc*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb532_pata_irq_handler ; 
 int /*<<< orphan*/  rb532_pata_setup_ports (struct ata_host*) ; 
 int /*<<< orphan*/  rb532_pata_sht ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int rb532_pata_driver_probe(struct platform_device *pdev)
{
	int irq;
	struct gpio_desc *gpiod;
	struct resource *res;
	struct ata_host *ah;
	struct rb532_cf_info *info;
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

	gpiod = devm_gpiod_get(&pdev->dev, NULL, GPIOD_IN);
	if (IS_ERR(gpiod)) {
		dev_err(&pdev->dev, "no GPIO found for irq%d\n", irq);
		return PTR_ERR(gpiod);
	}
	gpiod_set_consumer_name(gpiod, DRV_NAME);

	/* allocate host */
	ah = ata_host_alloc(&pdev->dev, RB500_CF_MAXPORTS);
	if (!ah)
		return -ENOMEM;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	ah->private_data = info;
	info->gpio_line = gpiod;
	info->irq = irq;

	info->iobase = devm_ioremap_nocache(&pdev->dev, res->start,
				resource_size(res));
	if (!info->iobase)
		return -ENOMEM;

	rb532_pata_setup_ports(ah);

	ret = ata_host_activate(ah, irq, rb532_pata_irq_handler,
				IRQF_TRIGGER_LOW, &rb532_pata_sht);
	if (ret)
		return ret;

	return 0;
}