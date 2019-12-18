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
typedef  int u32 ;
struct tpm_tis_data {scalar_t__ ilb_base_addr; int /*<<< orphan*/  locality; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TPM_GLOBAL_INT_ENABLE ; 
 int TPM_INT_ENABLE (int /*<<< orphan*/ ) ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  tpm_tis_clkrun_enable (struct tpm_chip*,int) ; 
 int tpm_tis_read32 (struct tpm_tis_data*,int,int*) ; 
 int /*<<< orphan*/  tpm_tis_write32 (struct tpm_tis_data*,int,int) ; 

void tpm_tis_remove(struct tpm_chip *chip)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 reg = TPM_INT_ENABLE(priv->locality);
	u32 interrupt;
	int rc;

	tpm_tis_clkrun_enable(chip, true);

	rc = tpm_tis_read32(priv, reg, &interrupt);
	if (rc < 0)
		interrupt = 0;

	tpm_tis_write32(priv, reg, ~TPM_GLOBAL_INT_ENABLE & interrupt);

	tpm_tis_clkrun_enable(chip, false);

	if (priv->ilb_base_addr)
		iounmap(priv->ilb_base_addr);
}