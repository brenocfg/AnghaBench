#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct tpm_tis_data {int irq; int irq_tested; int /*<<< orphan*/  locality; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct tpm_chip {int flags; TYPE_1__ dev; } ;

/* Variables and functions */
 int TPM_CHIP_FLAG_IRQ ; 
 int TPM_GLOBAL_INT_ENABLE ; 
 int /*<<< orphan*/  TPM_INT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_INT_STATUS (int /*<<< orphan*/ ) ; 
 int TPM_INT_VECTOR (int /*<<< orphan*/ ) ; 
 struct tpm_tis_data* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 scalar_t__ devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct tpm_chip*) ; 
 int /*<<< orphan*/  tis_int_handler ; 
 int tpm_tis_gen_interrupt (struct tpm_chip*) ; 
 int tpm_tis_read32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int*) ; 
 int tpm_tis_read8 (struct tpm_tis_data*,int,int*) ; 
 int tpm_tis_write32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int) ; 
 int tpm_tis_write8 (struct tpm_tis_data*,int,int) ; 

__attribute__((used)) static int tpm_tis_probe_irq_single(struct tpm_chip *chip, u32 intmask,
				    int flags, int irq)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u8 original_int_vec;
	int rc;
	u32 int_status;

	if (devm_request_irq(chip->dev.parent, irq, tis_int_handler, flags,
			     dev_name(&chip->dev), chip) != 0) {
		dev_info(&chip->dev, "Unable to request irq: %d for probe\n",
			 irq);
		return -1;
	}
	priv->irq = irq;

	rc = tpm_tis_read8(priv, TPM_INT_VECTOR(priv->locality),
			   &original_int_vec);
	if (rc < 0)
		return rc;

	rc = tpm_tis_write8(priv, TPM_INT_VECTOR(priv->locality), irq);
	if (rc < 0)
		return rc;

	rc = tpm_tis_read32(priv, TPM_INT_STATUS(priv->locality), &int_status);
	if (rc < 0)
		return rc;

	/* Clear all existing */
	rc = tpm_tis_write32(priv, TPM_INT_STATUS(priv->locality), int_status);
	if (rc < 0)
		return rc;

	/* Turn on */
	rc = tpm_tis_write32(priv, TPM_INT_ENABLE(priv->locality),
			     intmask | TPM_GLOBAL_INT_ENABLE);
	if (rc < 0)
		return rc;

	priv->irq_tested = false;

	/* Generate an interrupt by having the core call through to
	 * tpm_tis_send
	 */
	rc = tpm_tis_gen_interrupt(chip);
	if (rc < 0)
		return rc;

	/* tpm_tis_send will either confirm the interrupt is working or it
	 * will call disable_irq which undoes all of the above.
	 */
	if (!(chip->flags & TPM_CHIP_FLAG_IRQ)) {
		rc = tpm_tis_write8(priv, original_int_vec,
				TPM_INT_VECTOR(priv->locality));
		if (rc < 0)
			return rc;

		return 1;
	}

	return 0;
}