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
typedef  char u_char ;
struct sshkey {int /*<<< orphan*/ * dsa; int /*<<< orphan*/  type; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  DSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  DSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_SIG_new () ; 
 int /*<<< orphan*/  DSA_SIG_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DSA_do_verify (char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int INTBLOB_LEN ; 
 scalar_t__ KEY_DSA ; 
 size_t SIGBLOB_LEN ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int /*<<< orphan*/  SSH_DIGEST_SHA1 ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_TYPE_MISMATCH ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_ERR_SIGNATURE_INVALID ; 
 int SSH_ERR_UNEXPECTED_TRAILING_DATA ; 
 int /*<<< orphan*/  explicit_bzero (char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t ssh_digest_bytes (int /*<<< orphan*/ ) ; 
 int ssh_digest_memory (int /*<<< orphan*/ ,char const*,size_t,char*,int) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_from (char const*,size_t) ; 
 scalar_t__ sshbuf_get_cstring (struct sshbuf*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_get_string (struct sshbuf*,char**,size_t*) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 scalar_t__ sshkey_type_plain (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
ssh_dss_verify(const struct sshkey *key,
    const u_char *signature, size_t signaturelen,
    const u_char *data, size_t datalen, u_int compat)
{
	DSA_SIG *sig = NULL;
	BIGNUM *sig_r = NULL, *sig_s = NULL;
	u_char digest[SSH_DIGEST_MAX_LENGTH], *sigblob = NULL;
	size_t len, dlen = ssh_digest_bytes(SSH_DIGEST_SHA1);
	int ret = SSH_ERR_INTERNAL_ERROR;
	struct sshbuf *b = NULL;
	char *ktype = NULL;

	if (key == NULL || key->dsa == NULL ||
	    sshkey_type_plain(key->type) != KEY_DSA ||
	    signature == NULL || signaturelen == 0)
		return SSH_ERR_INVALID_ARGUMENT;
	if (dlen == 0)
		return SSH_ERR_INTERNAL_ERROR;

	/* fetch signature */
	if ((b = sshbuf_from(signature, signaturelen)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if (sshbuf_get_cstring(b, &ktype, NULL) != 0 ||
	    sshbuf_get_string(b, &sigblob, &len) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	if (strcmp("ssh-dss", ktype) != 0) {
		ret = SSH_ERR_KEY_TYPE_MISMATCH;
		goto out;
	}
	if (sshbuf_len(b) != 0) {
		ret = SSH_ERR_UNEXPECTED_TRAILING_DATA;
		goto out;
	}

	if (len != SIGBLOB_LEN) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}

	/* parse signature */
	if ((sig = DSA_SIG_new()) == NULL ||
	    (sig_r = BN_new()) == NULL ||
	    (sig_s = BN_new()) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((BN_bin2bn(sigblob, INTBLOB_LEN, sig_r) == NULL) ||
	    (BN_bin2bn(sigblob + INTBLOB_LEN, INTBLOB_LEN, sig_s) == NULL)) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	if (!DSA_SIG_set0(sig, sig_r, sig_s)) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	sig_r = sig_s = NULL; /* transferred */

	/* sha1 the data */
	if ((ret = ssh_digest_memory(SSH_DIGEST_SHA1, data, datalen,
	    digest, sizeof(digest))) != 0)
		goto out;

	switch (DSA_do_verify(digest, dlen, sig, key->dsa)) {
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
	DSA_SIG_free(sig);
	BN_clear_free(sig_r);
	BN_clear_free(sig_s);
	sshbuf_free(b);
	free(ktype);
	if (sigblob != NULL) {
		explicit_bzero(sigblob, len);
		free(sigblob);
	}
	return ret;
}