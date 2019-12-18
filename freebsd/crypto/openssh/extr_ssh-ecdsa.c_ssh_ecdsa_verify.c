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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int /*<<< orphan*/ * ecdsa; int /*<<< orphan*/  ecdsa_nid; int /*<<< orphan*/  type; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  ECDSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ECDSA_SIG_new () ; 
 int /*<<< orphan*/  ECDSA_SIG_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ECDSA_do_verify (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ KEY_ECDSA ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_TYPE_MISMATCH ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_ERR_SIGNATURE_INVALID ; 
 int SSH_ERR_UNEXPECTED_TRAILING_DATA ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t ssh_digest_bytes (int) ; 
 int ssh_digest_memory (int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_from (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ sshbuf_froms (struct sshbuf*,struct sshbuf**) ; 
 scalar_t__ sshbuf_get_bignum2 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_get_cstring (struct sshbuf*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int sshkey_ec_nid_to_hash_alg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_ssh_name_plain (struct sshkey const*) ; 
 scalar_t__ sshkey_type_plain (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
ssh_ecdsa_verify(const struct sshkey *key,
    const u_char *signature, size_t signaturelen,
    const u_char *data, size_t datalen, u_int compat)
{
	ECDSA_SIG *sig = NULL;
	BIGNUM *sig_r = NULL, *sig_s = NULL;
	int hash_alg;
	u_char digest[SSH_DIGEST_MAX_LENGTH];
	size_t dlen;
	int ret = SSH_ERR_INTERNAL_ERROR;
	struct sshbuf *b = NULL, *sigbuf = NULL;
	char *ktype = NULL;

	if (key == NULL || key->ecdsa == NULL ||
	    sshkey_type_plain(key->type) != KEY_ECDSA ||
	    signature == NULL || signaturelen == 0)
		return SSH_ERR_INVALID_ARGUMENT;

	if ((hash_alg = sshkey_ec_nid_to_hash_alg(key->ecdsa_nid)) == -1 ||
	    (dlen = ssh_digest_bytes(hash_alg)) == 0)
		return SSH_ERR_INTERNAL_ERROR;

	/* fetch signature */
	if ((b = sshbuf_from(signature, signaturelen)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if (sshbuf_get_cstring(b, &ktype, NULL) != 0 ||
	    sshbuf_froms(b, &sigbuf) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	if (strcmp(sshkey_ssh_name_plain(key), ktype) != 0) {
		ret = SSH_ERR_KEY_TYPE_MISMATCH;
		goto out;
	}
	if (sshbuf_len(b) != 0) {
		ret = SSH_ERR_UNEXPECTED_TRAILING_DATA;
		goto out;
	}

	/* parse signature */
	if ((sig = ECDSA_SIG_new()) == NULL ||
	    (sig_r = BN_new()) == NULL ||
	    (sig_s = BN_new()) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (sshbuf_get_bignum2(sigbuf, sig_r) != 0 ||
	    sshbuf_get_bignum2(sigbuf, sig_s) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	if (!ECDSA_SIG_set0(sig, sig_r, sig_s)) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	sig_r = sig_s = NULL; /* transferred */

	if (sshbuf_len(sigbuf) != 0) {
		ret = SSH_ERR_UNEXPECTED_TRAILING_DATA;
		goto out;
	}
	if ((ret = ssh_digest_memory(hash_alg, data, datalen,
	    digest, sizeof(digest))) != 0)
		goto out;

	switch (ECDSA_do_verify(digest, dlen, sig, key->ecdsa)) {
	case 1:
		ret = 0;
		break;
	case 0:
		ret = SSH_ERR_SIGNATURE_INVALID;
		goto out;
	default:
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}

 out:
	explicit_bzero(digest, sizeof(digest));
	sshbuf_free(sigbuf);
	sshbuf_free(b);
	ECDSA_SIG_free(sig);
	BN_clear_free(sig_r);
	BN_clear_free(sig_s);
	free(ktype);
	return ret;
}