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
struct trusted_key_payload {int dummy; } ;
struct trusted_key_options {int dummy; } ;
struct tpm_chip {int flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm2_seal_trusted (struct tpm_chip*,struct trusted_key_payload*,struct trusted_key_options*) ; 
 struct tpm_chip* tpm_find_get_ops (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 

int tpm_seal_trusted(struct tpm_chip *chip, struct trusted_key_payload *payload,
		     struct trusted_key_options *options)
{
	int rc;

	chip = tpm_find_get_ops(chip);
	if (!chip || !(chip->flags & TPM_CHIP_FLAG_TPM2))
		return -ENODEV;

	rc = tpm2_seal_trusted(chip, payload, options);

	tpm_put_ops(chip);
	return rc;
}