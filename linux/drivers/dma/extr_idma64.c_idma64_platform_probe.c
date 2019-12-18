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
struct resource {int dummy; } ;
struct device {struct device* parent; } ;
struct platform_device {struct device dev; } ;
struct idma64_chip {scalar_t__ irq; struct device* sysdev; struct device* dev; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct idma64_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int idma64_probe (struct idma64_chip*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct idma64_chip*) ; 

__attribute__((used)) static int idma64_platform_probe(struct platform_device *pdev)
{
	struct idma64_chip *chip;
	struct device *dev = &pdev->dev;
	struct device *sysdev = dev->parent;
	struct resource *mem;
	int ret;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->irq = platform_get_irq(pdev, 0);
	if (chip->irq < 0)
		return chip->irq;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	chip->regs = devm_ioremap_resource(dev, mem);
	if (IS_ERR(chip->regs))
		return PTR_ERR(chip->regs);

	ret = dma_coerce_mask_and_coherent(sysdev, DMA_BIT_MASK(64));
	if (ret)
		return ret;

	chip->dev = dev;
	chip->sysdev = sysdev;

	ret = idma64_probe(chip);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, chip);
	return 0;
}