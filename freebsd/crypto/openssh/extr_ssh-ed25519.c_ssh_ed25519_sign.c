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
struct sshkey {int /*<<< orphan*/ * ed25519_sk; int /*<<< orphan*/  type; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 size_t INT_MAX ; 
 scalar_t__ KEY_ED25519 ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int crypto_sign_ed25519 (int /*<<< orphan*/ *,unsigned long long*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 size_t crypto_sign_ed25519_BYTES ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 size_t sshbuf_len (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int sshbuf_put_cstring (struct sshbuf*,char*) ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ *,unsigned long long) ; 
 scalar_t__ sshkey_type_plain (int /*<<< orphan*/ ) ; 

int
ssh_ed25519_sign(const struct sshkey *key, u_char **sigp, size_t *lenp,
    const u_char *data, size_t datalen, u_int compat)
{
	u_char *sig = NULL;
	size_t slen = 0, len;
	unsigned long long smlen;
	int r, ret;
	struct sshbuf *b = NULL;

	if (lenp != NULL)
		*lenp = 0;
	if (sigp != NULL)
		*sigp = NULL;

	if (key == NULL ||
	    sshkey_type_plain(key->type) != KEY_ED25519 ||
	    key->ed25519_sk == NULL ||
	    datalen >= INT_MAX - crypto_sign_ed25519_BYTES)
		return SSH_ERR_INVALID_ARGUMENT;
	smlen = slen = datalen + crypto_sign_ed25519_BYTES;
	if ((sig = malloc(slen)) == NULL)
		return SSH_ERR_ALLOC_FAIL;

	if ((ret = crypto_sign_ed25519(sig, &smlen, data, datalen,
	    key->ed25519_sk)) != 0 || smlen <= datalen) {
		r = SSH_ERR_INVALID_ARGUMENT; /* XXX better error? */
		goto out;
	}
	/* encode signature */
	if ((b = sshbuf_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = sshbuf_put_cstring(b, "ssh-ed25519")) != 0 ||
	    (r = sshbuf_put_string(b, sig, smlen - datalen)) != 0)
		goto out;
	len = sshbuf_len(b);
	if (sigp != NULL) {
		if ((*sigp = malloc(len)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		memcpy(*sigp, sshbuf_ptr(b), len);
	}
	if (lenp != NULL)
		*lenp = len;
	/* success */
	r = 0;
 out:
	sshbuf_free(b);
	if (sig != NULL) {
		explicit_bzero(sig, slen);
		free(sig);
	}

	return r;
}