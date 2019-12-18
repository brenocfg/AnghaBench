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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct trusted_key_payload {int key_len; int /*<<< orphan*/  migratable; int /*<<< orphan*/  key; } ;
struct trusted_key_options {int /*<<< orphan*/  blobauth; scalar_t__ policyhandle; } ;
struct tpm_chip {int dummy; } ;
struct tpm_buf {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EFAULT ; 
 int EPERM ; 
 int MAX_KEY_SIZE ; 
 int MIN_KEY_SIZE ; 
 int /*<<< orphan*/  TPM2_CC_UNSEAL ; 
 scalar_t__ TPM2_RS_PW ; 
 int /*<<< orphan*/  TPM2_SA_CONTINUE_SESSION ; 
 int /*<<< orphan*/  TPM2_ST_SESSIONS ; 
 int /*<<< orphan*/  TPM_DIGEST_SIZE ; 
 int TPM_HEADER_SIZE ; 
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tpm2_buf_append_auth (struct tpm_buf*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm_buf_length (struct tpm_buf*) ; 
 int tpm_transmit_cmd (struct tpm_chip*,struct tpm_buf*,int,char*) ; 

__attribute__((used)) static int tpm2_unseal_cmd(struct tpm_chip *chip,
			   struct trusted_key_payload *payload,
			   struct trusted_key_options *options,
			   u32 blob_handle)
{
	struct tpm_buf buf;
	u16 data_len;
	u8 *data;
	int rc;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_UNSEAL);
	if (rc)
		return rc;

	tpm_buf_append_u32(&buf, blob_handle);
	tpm2_buf_append_auth(&buf,
			     options->policyhandle ?
			     options->policyhandle : TPM2_RS_PW,
			     NULL /* nonce */, 0,
			     TPM2_SA_CONTINUE_SESSION,
			     options->blobauth /* hmac */,
			     TPM_DIGEST_SIZE);

	rc = tpm_transmit_cmd(chip, &buf, 6, "unsealing");
	if (rc > 0)
		rc = -EPERM;

	if (!rc) {
		data_len = be16_to_cpup(
			(__be16 *) &buf.data[TPM_HEADER_SIZE + 4]);
		if (data_len < MIN_KEY_SIZE ||  data_len > MAX_KEY_SIZE + 1) {
			rc = -EFAULT;
			goto out;
		}

		if (tpm_buf_length(&buf) < TPM_HEADER_SIZE + 6 + data_len) {
			rc = -EFAULT;
			goto out;
		}
		data = &buf.data[TPM_HEADER_SIZE + 6];

		memcpy(payload->key, data, data_len - 1);
		payload->key_len = data_len - 1;
		payload->migratable = data[data_len - 1];
	}

out:
	tpm_buf_destroy(&buf);
	return rc;
}