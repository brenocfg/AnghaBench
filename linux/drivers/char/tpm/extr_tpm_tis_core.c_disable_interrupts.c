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
typedef  int /*<<< orphan*/  u32 ;
struct tpm_tis_data {scalar_t__ irq; int /*<<< orphan*/  locality; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct tpm_chip {int /*<<< orphan*/  flags; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_CHIP_FLAG_IRQ ; 
 int /*<<< orphan*/  TPM_GLOBAL_INT_ENABLE ; 
 int /*<<< orphan*/  TPM_INT_ENABLE (int /*<<< orphan*/ ) ; 
 struct tpm_tis_data* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct tpm_chip*) ; 
 int tpm_tis_read32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tpm_tis_write32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_interrupts(struct tpm_chip *chip)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 intmask;
	int rc;

	rc = tpm_tis_read32(priv, TPM_INT_ENABLE(priv->locality), &intmask);
	if (rc < 0)
		intmask = 0;

	intmask &= ~TPM_GLOBAL_INT_ENABLE;
	rc = tpm_tis_write32(priv, TPM_INT_ENABLE(priv->locality), intmask);

	devm_free_irq(chip->dev.parent, priv->irq, chip);
	priv->irq = 0;
	chip->flags &= ~TPM_CHIP_FLAG_IRQ;
}