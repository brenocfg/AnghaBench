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
typedef  scalar_t__ u32 ;
struct trusted_key_payload {unsigned int blob_len; int /*<<< orphan*/  blob; int /*<<< orphan*/  migratable; scalar_t__ key_len; int /*<<< orphan*/  key; } ;
struct trusted_key_options {scalar_t__ hash; scalar_t__ policydigest_len; int /*<<< orphan*/  policydigest; int /*<<< orphan*/  blobauth; int /*<<< orphan*/  keyauth; int /*<<< orphan*/  keyhandle; } ;
struct tpm_chip {int dummy; } ;
struct tpm_buf {int flags; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {scalar_t__ crypto_id; scalar_t__ tpm_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int E2BIG ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 unsigned int MAX_BLOB_SIZE ; 
 int /*<<< orphan*/  TPM2_CC_CREATE ; 
 int /*<<< orphan*/  TPM2_OA_USER_WITH_AUTH ; 
 scalar_t__ TPM2_RC_HASH ; 
 int /*<<< orphan*/  TPM2_RS_PW ; 
 int /*<<< orphan*/  TPM2_ST_SESSIONS ; 
 scalar_t__ TPM_ALG_KEYEDHASH ; 
 scalar_t__ TPM_ALG_NULL ; 
 int TPM_BUF_OVERFLOW ; 
 scalar_t__ TPM_DIGEST_SIZE ; 
 size_t TPM_HEADER_SIZE ; 
 unsigned int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tpm2_buf_append_auth (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* tpm2_hash_map ; 
 scalar_t__ tpm2_rc_value (int) ; 
 int /*<<< orphan*/  tpm_buf_append (struct tpm_buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tpm_buf_append_u16 (struct tpm_buf*,scalar_t__) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_append_u8 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t tpm_buf_length (struct tpm_buf*) ; 
 int tpm_transmit_cmd (struct tpm_chip*,struct tpm_buf*,int,char*) ; 

int tpm2_seal_trusted(struct tpm_chip *chip,
		      struct trusted_key_payload *payload,
		      struct trusted_key_options *options)
{
	unsigned int blob_len;
	struct tpm_buf buf;
	u32 hash;
	int i;
	int rc;

	for (i = 0; i < ARRAY_SIZE(tpm2_hash_map); i++) {
		if (options->hash == tpm2_hash_map[i].crypto_id) {
			hash = tpm2_hash_map[i].tpm_id;
			break;
		}
	}

	if (i == ARRAY_SIZE(tpm2_hash_map))
		return -EINVAL;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_CREATE);
	if (rc)
		return rc;

	tpm_buf_append_u32(&buf, options->keyhandle);
	tpm2_buf_append_auth(&buf, TPM2_RS_PW,
			     NULL /* nonce */, 0,
			     0 /* session_attributes */,
			     options->keyauth /* hmac */,
			     TPM_DIGEST_SIZE);

	/* sensitive */
	tpm_buf_append_u16(&buf, 4 + TPM_DIGEST_SIZE + payload->key_len + 1);

	tpm_buf_append_u16(&buf, TPM_DIGEST_SIZE);
	tpm_buf_append(&buf, options->blobauth, TPM_DIGEST_SIZE);
	tpm_buf_append_u16(&buf, payload->key_len + 1);
	tpm_buf_append(&buf, payload->key, payload->key_len);
	tpm_buf_append_u8(&buf, payload->migratable);

	/* public */
	tpm_buf_append_u16(&buf, 14 + options->policydigest_len);
	tpm_buf_append_u16(&buf, TPM_ALG_KEYEDHASH);
	tpm_buf_append_u16(&buf, hash);

	/* policy */
	if (options->policydigest_len) {
		tpm_buf_append_u32(&buf, 0);
		tpm_buf_append_u16(&buf, options->policydigest_len);
		tpm_buf_append(&buf, options->policydigest,
			       options->policydigest_len);
	} else {
		tpm_buf_append_u32(&buf, TPM2_OA_USER_WITH_AUTH);
		tpm_buf_append_u16(&buf, 0);
	}

	/* public parameters */
	tpm_buf_append_u16(&buf, TPM_ALG_NULL);
	tpm_buf_append_u16(&buf, 0);

	/* outside info */
	tpm_buf_append_u16(&buf, 0);

	/* creation PCR */
	tpm_buf_append_u32(&buf, 0);

	if (buf.flags & TPM_BUF_OVERFLOW) {
		rc = -E2BIG;
		goto out;
	}

	rc = tpm_transmit_cmd(chip, &buf, 4, "sealing data");
	if (rc)
		goto out;

	blob_len = be32_to_cpup((__be32 *) &buf.data[TPM_HEADER_SIZE]);
	if (blob_len > MAX_BLOB_SIZE) {
		rc = -E2BIG;
		goto out;
	}
	if (tpm_buf_length(&buf) < TPM_HEADER_SIZE + 4 + blob_len) {
		rc = -EFAULT;
		goto out;
	}

	memcpy(payload->blob, &buf.data[TPM_HEADER_SIZE + 4], blob_len);
	payload->blob_len = blob_len;

out:
	tpm_buf_destroy(&buf);

	if (rc > 0) {
		if (tpm2_rc_value(rc) == TPM2_RC_HASH)
			rc = -EINVAL;
		else
			rc = -EPERM;
	}

	return rc;
}