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
struct mpc52xx_ata_priv {int ata_irq; int /*<<< orphan*/  dmatsk; } ;
struct ata_host {struct mpc52xx_ata_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_platform_remove_one (struct platform_device*) ; 
 int /*<<< orphan*/  bcom_ata_release (int /*<<< orphan*/ ) ; 
 int bcom_get_task_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 struct ata_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int
mpc52xx_ata_remove(struct platform_device *op)
{
	struct ata_host *host = platform_get_drvdata(op);
	struct mpc52xx_ata_priv *priv = host->private_data;
	int task_irq;

	/* Deregister the ATA interface */
	ata_platform_remove_one(op);

	/* Clean up DMA */
	task_irq = bcom_get_task_irq(priv->dmatsk);
	irq_dispose_mapping(task_irq);
	bcom_ata_release(priv->dmatsk);
	irq_dispose_mapping(priv->ata_irq);

	return 0;
}