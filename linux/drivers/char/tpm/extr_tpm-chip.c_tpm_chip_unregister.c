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
struct tpm_chip {int flags; int /*<<< orphan*/  devs; int /*<<< orphan*/  cdevs; int /*<<< orphan*/  hwrng; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HW_RANDOM_TPM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm_bios_log_teardown (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_del_char_device (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_del_legacy_sysfs (struct tpm_chip*) ; 

void tpm_chip_unregister(struct tpm_chip *chip)
{
	tpm_del_legacy_sysfs(chip);
	if (IS_ENABLED(CONFIG_HW_RANDOM_TPM))
		hwrng_unregister(&chip->hwrng);
	tpm_bios_log_teardown(chip);
	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		cdev_device_del(&chip->cdevs, &chip->devs);
	tpm_del_char_device(chip);
}