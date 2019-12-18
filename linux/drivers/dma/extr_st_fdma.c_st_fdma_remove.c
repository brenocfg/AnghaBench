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
struct st_fdma_dev {int /*<<< orphan*/  slim_rproc; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (TYPE_1__*,int /*<<< orphan*/ ,struct st_fdma_dev*) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct st_fdma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  st_slim_rproc_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_fdma_remove(struct platform_device *pdev)
{
	struct st_fdma_dev *fdev = platform_get_drvdata(pdev);

	devm_free_irq(&pdev->dev, fdev->irq, fdev);
	st_slim_rproc_put(fdev->slim_rproc);
	of_dma_controller_free(pdev->dev.of_node);

	return 0;
}