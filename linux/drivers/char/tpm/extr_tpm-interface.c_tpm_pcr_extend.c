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
struct tpm_digest {scalar_t__ alg_id; int /*<<< orphan*/  digest; } ;
struct tpm_chip {int nr_allocated_banks; int flags; TYPE_1__* allocated_banks; } ;
struct TYPE_2__ {scalar_t__ alg_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm1_pcr_extend (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int tpm2_pcr_extend (struct tpm_chip*,int /*<<< orphan*/ ,struct tpm_digest*) ; 
 struct tpm_chip* tpm_find_get_ops (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 

int tpm_pcr_extend(struct tpm_chip *chip, u32 pcr_idx,
		   struct tpm_digest *digests)
{
	int rc;
	int i;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		return -ENODEV;

	for (i = 0; i < chip->nr_allocated_banks; i++) {
		if (digests[i].alg_id != chip->allocated_banks[i].alg_id) {
			rc = EINVAL;
			goto out;
		}
	}

	if (chip->flags & TPM_CHIP_FLAG_TPM2) {
		rc = tpm2_pcr_extend(chip, pcr_idx, digests);
		goto out;
	}

	rc = tpm1_pcr_extend(chip, pcr_idx, digests[0].digest,
			     "attempting extend a PCR value");

out:
	tpm_put_ops(chip);
	return rc;
}