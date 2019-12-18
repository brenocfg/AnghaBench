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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dw_dma_chip_pdata {int (* remove ) (struct dw_dma_chip*) ;struct dw_dma_chip* chip; } ;
struct dw_dma_chip {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dw_dma_acpi_controller_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_of_controller_free (int /*<<< orphan*/ ) ; 
 struct dw_dma_chip_pdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int stub1 (struct dw_dma_chip*) ; 

__attribute__((used)) static int dw_remove(struct platform_device *pdev)
{
	struct dw_dma_chip_pdata *data = platform_get_drvdata(pdev);
	struct dw_dma_chip *chip = data->chip;
	int ret;

	dw_dma_acpi_controller_free(chip->dw);

	dw_dma_of_controller_free(chip->dw);

	ret = data->remove(chip);
	if (ret)
		dev_warn(chip->dev, "can't remove device properly: %d\n", ret);

	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(chip->clk);

	return 0;
}