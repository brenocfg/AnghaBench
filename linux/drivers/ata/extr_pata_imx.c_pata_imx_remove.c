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
struct pata_imx_priv {int /*<<< orphan*/  clk; scalar_t__ host_regs; } ;
struct ata_host {struct pata_imx_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ PATA_IMX_ATA_INT_EN ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ata_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pata_imx_remove(struct platform_device *pdev)
{
	struct ata_host *host = platform_get_drvdata(pdev);
	struct pata_imx_priv *priv = host->private_data;

	ata_host_detach(host);

	__raw_writel(0, priv->host_regs + PATA_IMX_ATA_INT_EN);

	clk_disable_unprepare(priv->clk);

	return 0;
}