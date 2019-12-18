#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct sshkey {TYPE_1__* cert; } ;
struct sshbuf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {scalar_t__ type; char* key_id; scalar_t__ nprincipals; char** principals; struct sshbuf* certblob; TYPE_2__* signature_key; struct sshbuf* extensions; struct sshbuf* critical; int /*<<< orphan*/  valid_before; int /*<<< orphan*/  valid_after; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 scalar_t__ SSH2_CERT_TYPE_HOST ; 
 scalar_t__ SSH2_CERT_TYPE_USER ; 
 scalar_t__ SSHKEY_CERT_MAX_PRINCIPALS ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_CERT_INVALID_SIGN_KEY ; 
 int SSH_ERR_KEY_CERT_UNKNOWN_TYPE ; 
 int /*<<< orphan*/  free (char*) ; 
 char** recallocarray (char**,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int sshbuf_froms (struct sshbuf*,struct sshbuf**) ; 
 int sshbuf_get_cstring (struct sshbuf*,char**,size_t*) ; 
 int sshbuf_get_string (struct sshbuf*,char**,size_t*) ; 
 int sshbuf_get_string_direct (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sshbuf_get_u32 (struct sshbuf*,scalar_t__*) ; 
 int sshbuf_get_u64 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int sshbuf_putb (struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 
 scalar_t__ sshkey_from_blob_internal (struct sshbuf*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_type_is_valid_ca (int /*<<< orphan*/ ) ; 
 int sshkey_verify (TYPE_2__*,char*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cert_parse(struct sshbuf *b, struct sshkey *key, struct sshbuf *certbuf)
{
	struct sshbuf *principals = NULL, *crit = NULL;
	struct sshbuf *exts = NULL, *ca = NULL;
	u_char *sig = NULL;
	size_t signed_len = 0, slen = 0, kidlen = 0;
	int ret = SSH_ERR_INTERNAL_ERROR;

	/* Copy the entire key blob for verification and later serialisation */
	if ((ret = sshbuf_putb(key->cert->certblob, certbuf)) != 0)
		return ret;

	/* Parse body of certificate up to signature */
	if ((ret = sshbuf_get_u64(b, &key->cert->serial)) != 0 ||
	    (ret = sshbuf_get_u32(b, &key->cert->type)) != 0 ||
	    (ret = sshbuf_get_cstring(b, &key->cert->key_id, &kidlen)) != 0 ||
	    (ret = sshbuf_froms(b, &principals)) != 0 ||
	    (ret = sshbuf_get_u64(b, &key->cert->valid_after)) != 0 ||
	    (ret = sshbuf_get_u64(b, &key->cert->valid_before)) != 0 ||
	    (ret = sshbuf_froms(b, &crit)) != 0 ||
	    (ret = sshbuf_froms(b, &exts)) != 0 ||
	    (ret = sshbuf_get_string_direct(b, NULL, NULL)) != 0 ||
	    (ret = sshbuf_froms(b, &ca)) != 0) {
		/* XXX debug print error for ret */
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}

	/* Signature is left in the buffer so we can calculate this length */
	signed_len = sshbuf_len(key->cert->certblob) - sshbuf_len(b);

	if ((ret = sshbuf_get_string(b, &sig, &slen)) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}

	if (key->cert->type != SSH2_CERT_TYPE_USER &&
	    key->cert->type != SSH2_CERT_TYPE_HOST) {
		ret = SSH_ERR_KEY_CERT_UNKNOWN_TYPE;
		goto out;
	}

	/* Parse principals section */
	while (sshbuf_len(principals) > 0) {
		char *principal = NULL;
		char **oprincipals = NULL;

		if (key->cert->nprincipals >= SSHKEY_CERT_MAX_PRINCIPALS) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		if ((ret = sshbuf_get_cstring(principals, &principal,
		    NULL)) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		oprincipals = key->cert->principals;
		key->cert->principals = recallocarray(key->cert->principals,
		    key->cert->nprincipals, key->cert->nprincipals + 1,
		    sizeof(*key->cert->principals));
		if (key->cert->principals == NULL) {
			free(principal);
			key->cert->principals = oprincipals;
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		key->cert->principals[key->cert->nprincipals++] = principal;
	}

	/*
	 * Stash a copies of the critical options and extensions sections
	 * for later use.
	 */
	if ((ret = sshbuf_putb(key->cert->critical, crit)) != 0 ||
	    (exts != NULL &&
	    (ret = sshbuf_putb(key->cert->extensions, exts)) != 0))
		goto out;

	/*
	 * Validate critical options and extensions sections format.
	 */
	while (sshbuf_len(crit) != 0) {
		if ((ret = sshbuf_get_string_direct(crit, NULL, NULL)) != 0 ||
		    (ret = sshbuf_get_string_direct(crit, NULL, NULL)) != 0) {
			sshbuf_reset(key->cert->critical);
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
	}
	while (exts != NULL && sshbuf_len(exts) != 0) {
		if ((ret = sshbuf_get_string_direct(exts, NULL, NULL)) != 0 ||
		    (ret = sshbuf_get_string_direct(exts, NULL, NULL)) != 0) {
			sshbuf_reset(key->cert->extensions);
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
	}

	/* Parse CA key and check signature */
	if (sshkey_from_blob_internal(ca, &key->cert->signature_key, 0) != 0) {
		ret = SSH_ERR_KEY_CERT_INVALID_SIGN_KEY;
		goto out;
	}
	if (!sshkey_type_is_valid_ca(key->cert->signature_key->type)) {
		ret = SSH_ERR_KEY_CERT_INVALID_SIGN_KEY;
		goto out;
	}
	if ((ret = sshkey_verify(key->cert->signature_key, sig, slen,
	    sshbuf_ptr(key->cert->certblob), signed_len, NULL, 0)) != 0)
		goto out;

	/* Success */
	ret = 0;
 out:
	sshbuf_free(ca);
	sshbuf_free(crit);
	sshbuf_free(exts);
	sshbuf_free(principals);
	free(sig);
	return ret;
}