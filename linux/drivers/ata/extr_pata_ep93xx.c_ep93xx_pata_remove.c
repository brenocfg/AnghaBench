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
struct platform_device {int dummy; } ;
struct ep93xx_pata_data {int /*<<< orphan*/  ide_base; } ;
struct ata_host {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  ep93xx_ide_release_gpio (struct platform_device*) ; 
 int /*<<< orphan*/  ep93xx_pata_clear_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pata_release_dma (struct ep93xx_pata_data*) ; 
 struct ata_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ep93xx_pata_remove(struct platform_device *pdev)
{
	struct ata_host *host = platform_get_drvdata(pdev);
	struct ep93xx_pata_data *drv_data = host->private_data;

	ata_host_detach(host);
	ep93xx_pata_release_dma(drv_data);
	ep93xx_pata_clear_regs(drv_data->ide_base);
	ep93xx_ide_release_gpio(pdev);
	return 0;
}