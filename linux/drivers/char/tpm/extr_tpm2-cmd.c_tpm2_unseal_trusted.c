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
struct trusted_key_payload {int dummy; } ;
struct trusted_key_options {int dummy; } ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpm2_flush_context (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int tpm2_load_cmd (struct tpm_chip*,struct trusted_key_payload*,struct trusted_key_options*,int /*<<< orphan*/ *) ; 
 int tpm2_unseal_cmd (struct tpm_chip*,struct trusted_key_payload*,struct trusted_key_options*,int /*<<< orphan*/ ) ; 

int tpm2_unseal_trusted(struct tpm_chip *chip,
			struct trusted_key_payload *payload,
			struct trusted_key_options *options)
{
	u32 blob_handle;
	int rc;

	rc = tpm2_load_cmd(chip, payload, options, &blob_handle);
	if (rc)
		return rc;

	rc = tpm2_unseal_cmd(chip, payload, options, blob_handle);
	tpm2_flush_context(chip, blob_handle);
	return rc;
}