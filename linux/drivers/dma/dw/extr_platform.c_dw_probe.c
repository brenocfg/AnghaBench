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
struct device {int dummy; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  id; } ;
struct dw_dma_chip_pdata {int (* probe ) (struct dw_dma_chip*) ;struct dw_dma_chip* chip; scalar_t__ pdata; } ;
struct dw_dma_chip {scalar_t__ irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  dw; struct device* dev; scalar_t__ pdata; int /*<<< orphan*/  id; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_get_platdata (struct device*) ; 
 struct dw_dma_chip_pdata* device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 struct dw_dma_chip_pdata* devm_kmemdup (struct device*,struct dw_dma_chip_pdata const*,int,int /*<<< orphan*/ ) ; 
 struct dw_dma_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_acpi_controller_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_of_controller_register (int /*<<< orphan*/ ) ; 
 scalar_t__ dw_dma_parse_dt (struct platform_device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_dma_chip_pdata*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int stub1 (struct dw_dma_chip*) ; 

__attribute__((used)) static int dw_probe(struct platform_device *pdev)
{
	const struct dw_dma_chip_pdata *match;
	struct dw_dma_chip_pdata *data;
	struct dw_dma_chip *chip;
	struct device *dev = &pdev->dev;
	int err;

	match = device_get_match_data(dev);
	if (!match)
		return -ENODEV;

	data = devm_kmemdup(&pdev->dev, match, sizeof(*match), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->irq = platform_get_irq(pdev, 0);
	if (chip->irq < 0)
		return chip->irq;

	chip->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(chip->regs))
		return PTR_ERR(chip->regs);

	err = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (err)
		return err;

	if (!data->pdata)
		data->pdata = dev_get_platdata(dev);
	if (!data->pdata)
		data->pdata = dw_dma_parse_dt(pdev);

	chip->dev = dev;
	chip->id = pdev->id;
	chip->pdata = data->pdata;

	data->chip = chip;

	chip->clk = devm_clk_get(chip->dev, "hclk");
	if (IS_ERR(chip->clk))
		return PTR_ERR(chip->clk);
	err = clk_prepare_enable(chip->clk);
	if (err)
		return err;

	pm_runtime_enable(&pdev->dev);

	err = data->probe(chip);
	if (err)
		goto err_dw_dma_probe;

	platform_set_drvdata(pdev, data);

	dw_dma_of_controller_register(chip->dw);

	dw_dma_acpi_controller_register(chip->dw);

	return 0;

err_dw_dma_probe:
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(chip->clk);
	return err;
}