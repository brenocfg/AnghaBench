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
typedef  int /*<<< orphan*/  u32 ;
struct tpm_digest {int /*<<< orphan*/  digest; } ;
struct tpm_chip {int flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm1_pcr_read (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm2_pcr_read (struct tpm_chip*,int /*<<< orphan*/ ,struct tpm_digest*,int /*<<< orphan*/ *) ; 
 struct tpm_chip* tpm_find_get_ops (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 

int tpm_pcr_read(struct tpm_chip *chip, u32 pcr_idx,
		 struct tpm_digest *digest)
{
	int rc;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		return -ENODEV;

	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm2_pcr_read(chip, pcr_idx, digest, NULL);
	else
		rc = tpm1_pcr_read(chip, pcr_idx, digest->digest);

	tpm_put_ops(chip);
	return rc;
}