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
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int /*<<< orphan*/ * rsa; int /*<<< orphan*/  type; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_num_bits (int /*<<< orphan*/  const*) ; 
 scalar_t__ KEY_RSA ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t RSA_size (int /*<<< orphan*/ *) ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_BITS_MISMATCH ; 
 int SSH_ERR_KEY_LENGTH ; 
 int SSH_ERR_KEY_TYPE_MISMATCH ; 
 int SSH_ERR_SIGNATURE_INVALID ; 
 int SSH_ERR_UNEXPECTED_TRAILING_DATA ; 
 scalar_t__ SSH_RSA_MINIMUM_MODULUS_SIZE ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freezero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int openssh_RSA_verify (int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 
 int rsa_hash_id_from_ident (char*) ; 
 int rsa_hash_id_from_keyname (char const*) ; 
 size_t ssh_digest_bytes (int) ; 
 int ssh_digest_memory (int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_from (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ sshbuf_get_cstring (struct sshbuf*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_get_string (struct sshbuf*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 scalar_t__ sshkey_type_plain (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
ssh_rsa_verify(const struct sshkey *key,
    const u_char *sig, size_t siglen, const u_char *data, size_t datalen,
    const char *alg)
{
	const BIGNUM *rsa_n;
	char *sigtype = NULL;
	int hash_alg, want_alg, ret = SSH_ERR_INTERNAL_ERROR;
	size_t len = 0, diff, modlen, dlen;
	struct sshbuf *b = NULL;
	u_char digest[SSH_DIGEST_MAX_LENGTH], *osigblob, *sigblob = NULL;

	if (key == NULL || key->rsa == NULL ||
	    sshkey_type_plain(key->type) != KEY_RSA ||
	    sig == NULL || siglen == 0)
		return SSH_ERR_INVALID_ARGUMENT;
	RSA_get0_key(key->rsa, &rsa_n, NULL, NULL);
	if (BN_num_bits(rsa_n) < SSH_RSA_MINIMUM_MODULUS_SIZE)
		return SSH_ERR_KEY_LENGTH;

	if ((b = sshbuf_from(sig, siglen)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if (sshbuf_get_cstring(b, &sigtype, NULL) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	if ((hash_alg = rsa_hash_id_from_ident(sigtype)) == -1) {
		ret = SSH_ERR_KEY_TYPE_MISMATCH;
		goto out;
	}
	/*
	 * Allow ssh-rsa-cert-v01 certs to generate SHA2 signatures for
	 * legacy reasons, but otherwise the signature type should match.
	 */
	if (alg != NULL && strcmp(alg, "ssh-rsa-cert-v01@openssh.com") != 0) {
		if ((want_alg = rsa_hash_id_from_keyname(alg)) == -1) {
			ret = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		if (hash_alg != want_alg) {
			ret = SSH_ERR_SIGNATURE_INVALID;
			goto out;
		}
	}
	if (sshbuf_get_string(b, &sigblob, &len) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	if (sshbuf_len(b) != 0) {
		ret = SSH_ERR_UNEXPECTED_TRAILING_DATA;
		goto out;
	}
	/* RSA_verify expects a signature of RSA_size */
	modlen = RSA_size(key->rsa);
	if (len > modlen) {
		ret = SSH_ERR_KEY_BITS_MISMATCH;
		goto out;
	} else if (len < modlen) {
		diff = modlen - len;
		osigblob = sigblob;
		if ((sigblob = realloc(sigblob, modlen)) == NULL) {
			sigblob = osigblob; /* put it back for clear/free */
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		memmove(sigblob + diff, sigblob, len);
		explicit_bzero(sigblob, diff);
		len = modlen;
	}
	if ((dlen = ssh_digest_bytes(hash_alg)) == 0) {
		ret = SSH_ERR_INTERNAL_ERROR;
		goto out;
	}
	if ((ret = ssh_digest_memory(hash_alg, data, datalen,
	    digest, sizeof(digest))) != 0)
		goto out;

	ret = openssh_RSA_verify(hash_alg, digest, dlen, sigblob, len,
	    key->rsa);
 out:
	freezero(sigblob, len);
	free(sigtype);
	sshbuf_free(b);
	explicit_bzero(digest, sizeof(digest));
	return ret;
}