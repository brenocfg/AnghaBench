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
struct tpm_chip {int nr_allocated_banks; TYPE_1__* allocated_banks; } ;
struct TYPE_2__ {size_t crypto_id; int /*<<< orphan*/  digest_size; int /*<<< orphan*/  alg_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HASH_ALGO_SHA1 ; 
 int /*<<< orphan*/  TPM_ALG_SHA1 ; 
 int /*<<< orphan*/ * hash_digest_size ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

int tpm1_get_pcr_allocation(struct tpm_chip *chip)
{
	chip->allocated_banks = kcalloc(1, sizeof(*chip->allocated_banks),
					GFP_KERNEL);
	if (!chip->allocated_banks)
		return -ENOMEM;

	chip->allocated_banks[0].alg_id = TPM_ALG_SHA1;
	chip->allocated_banks[0].digest_size = hash_digest_size[HASH_ALGO_SHA1];
	chip->allocated_banks[0].crypto_id = HASH_ALGO_SHA1;
	chip->nr_allocated_banks = 1;

	return 0;
}