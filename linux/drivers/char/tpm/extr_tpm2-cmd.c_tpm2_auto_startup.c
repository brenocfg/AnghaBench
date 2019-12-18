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
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int TPM2_RC_INITIALIZE ; 
 int tpm2_do_selftest (struct tpm_chip*) ; 
 int tpm2_get_cc_attrs_tbl (struct tpm_chip*) ; 
 int tpm2_get_timeouts (struct tpm_chip*) ; 
 int tpm2_startup (struct tpm_chip*) ; 

int tpm2_auto_startup(struct tpm_chip *chip)
{
	int rc;

	rc = tpm2_get_timeouts(chip);
	if (rc)
		goto out;

	rc = tpm2_do_selftest(chip);
	if (rc && rc != TPM2_RC_INITIALIZE)
		goto out;

	if (rc == TPM2_RC_INITIALIZE) {
		rc = tpm2_startup(chip);
		if (rc)
			goto out;

		rc = tpm2_do_selftest(chip);
		if (rc)
			goto out;
	}

	rc = tpm2_get_cc_attrs_tbl(chip);

out:
	if (rc > 0)
		rc = -ENODEV;
	return rc;
}