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
struct tpm_chip {int flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TPM2_SU_STATE ; 
 int TPM_CHIP_FLAG_ALWAYS_POWERED ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 struct tpm_chip* dev_get_drvdata (struct device*) ; 
 int tpm1_pm_suspend (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm2_shutdown (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_chip_start (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_chip_stop (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_suspend_pcr ; 

int tpm_pm_suspend(struct device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);
	int rc = 0;

	if (!chip)
		return -ENODEV;

	if (chip->flags & TPM_CHIP_FLAG_ALWAYS_POWERED)
		return 0;

	if (!tpm_chip_start(chip)) {
		if (chip->flags & TPM_CHIP_FLAG_TPM2)
			tpm2_shutdown(chip, TPM2_SU_STATE);
		else
			rc = tpm1_pm_suspend(chip, tpm_suspend_pcr);

		tpm_chip_stop(chip);
	}

	return rc;
}