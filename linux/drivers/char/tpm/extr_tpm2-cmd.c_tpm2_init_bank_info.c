#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tpm_digest {scalar_t__ alg_id; } ;
struct tpm_chip {struct tpm_bank_info* allocated_banks; } ;
struct tpm_bank_info {scalar_t__ alg_id; int crypto_id; int /*<<< orphan*/  digest_size; } ;
typedef  enum hash_algo { ____Placeholder_hash_algo } hash_algo ;
struct TYPE_3__ {int crypto_id; scalar_t__ tpm_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ * hash_digest_size ; 
 TYPE_1__* tpm2_hash_map ; 
 int tpm2_pcr_read (struct tpm_chip*,int /*<<< orphan*/ ,struct tpm_digest*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm2_init_bank_info(struct tpm_chip *chip, u32 bank_index)
{
	struct tpm_bank_info *bank = chip->allocated_banks + bank_index;
	struct tpm_digest digest = { .alg_id = bank->alg_id };
	int i;

	/*
	 * Avoid unnecessary PCR read operations to reduce overhead
	 * and obtain identifiers of the crypto subsystem.
	 */
	for (i = 0; i < ARRAY_SIZE(tpm2_hash_map); i++) {
		enum hash_algo crypto_algo = tpm2_hash_map[i].crypto_id;

		if (bank->alg_id != tpm2_hash_map[i].tpm_id)
			continue;

		bank->digest_size = hash_digest_size[crypto_algo];
		bank->crypto_id = crypto_algo;
		return 0;
	}

	return tpm2_pcr_read(chip, 0, &digest, &bank->digest_size);
}