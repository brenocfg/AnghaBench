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
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int tpm1_do_selftest (struct tpm_chip*) ; 
 int tpm1_get_timeouts (struct tpm_chip*) ; 

int tpm1_auto_startup(struct tpm_chip *chip)
{
	int rc;

	rc = tpm1_get_timeouts(chip);
	if (rc)
		goto out;
	rc = tpm1_do_selftest(chip);
	if (rc) {
		dev_err(&chip->dev, "TPM self test failed\n");
		goto out;
	}

	return rc;
out:
	if (rc > 0)
		rc = -ENODEV;
	return rc;
}