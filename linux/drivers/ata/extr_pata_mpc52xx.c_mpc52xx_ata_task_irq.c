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
struct mpc52xx_ata_priv {int /*<<< orphan*/  waiting_for_dma; int /*<<< orphan*/  dmatsk; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bcom_buffer_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_retrieve_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
mpc52xx_ata_task_irq(int irq, void *vpriv)
{
	struct mpc52xx_ata_priv *priv = vpriv;
	while (bcom_buffer_done(priv->dmatsk))
		bcom_retrieve_buffer(priv->dmatsk, NULL, NULL);

	priv->waiting_for_dma |= ATA_DMA_INTR;

	return IRQ_HANDLED;
}