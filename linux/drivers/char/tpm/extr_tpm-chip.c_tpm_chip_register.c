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
struct tpm_chip {int /*<<< orphan*/  hwrng; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HW_RANDOM_TPM ; 
 int ENODEV ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 int tpm_add_char_device (struct tpm_chip*) ; 
 int tpm_add_hwrng (struct tpm_chip*) ; 
 int tpm_add_legacy_sysfs (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_add_ppi (struct tpm_chip*) ; 
 int tpm_auto_startup (struct tpm_chip*) ; 
 int tpm_bios_log_setup (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_bios_log_teardown (struct tpm_chip*) ; 
 int tpm_chip_start (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_chip_stop (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 
 int tpm_get_pcr_allocation (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_sysfs_add_device (struct tpm_chip*) ; 

int tpm_chip_register(struct tpm_chip *chip)
{
	int rc;

	rc = tpm_chip_start(chip);
	if (rc)
		return rc;
	rc = tpm_auto_startup(chip);
	if (rc) {
		tpm_chip_stop(chip);
		return rc;
	}

	rc = tpm_get_pcr_allocation(chip);
	tpm_chip_stop(chip);
	if (rc)
		return rc;

	tpm_sysfs_add_device(chip);

	rc = tpm_bios_log_setup(chip);
	if (rc != 0 && rc != -ENODEV)
		return rc;

	tpm_add_ppi(chip);

	rc = tpm_add_hwrng(chip);
	if (rc)
		goto out_ppi;

	rc = tpm_add_char_device(chip);
	if (rc)
		goto out_hwrng;

	rc = tpm_add_legacy_sysfs(chip);
	if (rc) {
		tpm_chip_unregister(chip);
		return rc;
	}

	return 0;

out_hwrng:
	if (IS_ENABLED(CONFIG_HW_RANDOM_TPM))
		hwrng_unregister(&chip->hwrng);
out_ppi:
	tpm_bios_log_teardown(chip);

	return rc;
}