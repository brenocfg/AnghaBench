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
struct sshkey {int /*<<< orphan*/ * dsa; int /*<<< orphan*/  type; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  DSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 size_t BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_SIG_get0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * DSA_do_sign (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 size_t INTBLOB_LEN ; 
 scalar_t__ KEY_DSA ; 
 int SIGBLOB_LEN ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int /*<<< orphan*/  SSH_DIGEST_SHA1 ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t ssh_digest_bytes (int /*<<< orphan*/ ) ; 
 int ssh_digest_memory (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 size_t sshbuf_len (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int sshbuf_put_cstring (struct sshbuf*,char*) ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sshkey_type_plain (int /*<<< orphan*/ ) ; 

int
ssh_dss_sign(const struct sshkey *key, u_char **sigp, size_t *lenp,
    const u_char *data, size_t datalen, u_int compat)
{
	DSA_SIG *sig = NULL;
	const BIGNUM *sig_r, *sig_s;
	u_char digest[SSH_DIGEST_MAX_LENGTH], sigblob[SIGBLOB_LEN];
	size_t rlen, slen, len, dlen = ssh_digest_bytes(SSH_DIGEST_SHA1);
	struct sshbuf *b = NULL;
	int ret = SSH_ERR_INVALID_ARGUMENT;

	if (lenp != NULL)
		*lenp = 0;
	if (sigp != NULL)
		*sigp = NULL;

	if (key == NULL || key->dsa == NULL ||
	    sshkey_type_plain(key->type) != KEY_DSA)
		return SSH_ERR_INVALID_ARGUMENT;
	if (dlen == 0)
		return SSH_ERR_INTERNAL_ERROR;

	if ((ret = ssh_digest_memory(SSH_DIGEST_SHA1, data, datalen,
	    digest, sizeof(digest))) != 0)
		goto out;

	if ((sig = DSA_do_sign(digest, dlen, key->dsa)) == NULL) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}

	DSA_SIG_get0(sig, &sig_r, &sig_s);
	rlen = BN_num_bytes(sig_r);
	slen = BN_num_bytes(sig_s);
	if (rlen > INTBLOB_LEN || slen > INTBLOB_LEN) {
		ret = SSH_ERR_INTERNAL_ERROR;
		goto out;
	}
	explicit_bzero(sigblob, SIGBLOB_LEN);
	BN_bn2bin(sig_r, sigblob + SIGBLOB_LEN - INTBLOB_LEN - rlen);
	BN_bn2bin(sig_s, sigblob + SIGBLOB_LEN - slen);

	if ((b = sshbuf_new()) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((ret = sshbuf_put_cstring(b, "ssh-dss")) != 0 ||
	    (ret = sshbuf_put_string(b, sigblob, SIGBLOB_LEN)) != 0)
		goto out;

	len = sshbuf_len(b);
	if (sigp != NULL) {
		if ((*sigp = malloc(len)) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		memcpy(*sigp, sshbuf_ptr(b), len);
	}
	if (lenp != NULL)
		*lenp = len;
	ret = 0;
 out:
	explicit_bzero(digest, sizeof(digest));
	DSA_SIG_free(sig);
	sshbuf_free(b);
	return ret;
}