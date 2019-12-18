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
typedef  size_t u_int ;
struct sshkey_cert {size_t nprincipals; int /*<<< orphan*/ ** principals; int /*<<< orphan*/ * signature_key; int /*<<< orphan*/  valid_before; int /*<<< orphan*/  valid_after; int /*<<< orphan*/ * key_id; int /*<<< orphan*/  type; int /*<<< orphan*/  serial; int /*<<< orphan*/  extensions; int /*<<< orphan*/  critical; int /*<<< orphan*/  certblob; } ;
struct sshkey {struct sshkey_cert* cert; } ;

/* Variables and functions */
 size_t SSHKEY_CERT_MAX_PRINCIPALS ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/ ** calloc (size_t,int) ; 
 int /*<<< orphan*/  cert_free (struct sshkey_cert*) ; 
 struct sshkey_cert* cert_new () ; 
 int sshbuf_putb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshkey_from_private (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* strdup (int /*<<< orphan*/ *) ; 

int
sshkey_cert_copy(const struct sshkey *from_key, struct sshkey *to_key)
{
	u_int i;
	const struct sshkey_cert *from;
	struct sshkey_cert *to;
	int ret = SSH_ERR_INTERNAL_ERROR;

	if (to_key->cert != NULL) {
		cert_free(to_key->cert);
		to_key->cert = NULL;
	}

	if ((from = from_key->cert) == NULL)
		return SSH_ERR_INVALID_ARGUMENT;

	if ((to = to_key->cert = cert_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;

	if ((ret = sshbuf_putb(to->certblob, from->certblob)) != 0 ||
	    (ret = sshbuf_putb(to->critical, from->critical)) != 0 ||
	    (ret = sshbuf_putb(to->extensions, from->extensions)) != 0)
		return ret;

	to->serial = from->serial;
	to->type = from->type;
	if (from->key_id == NULL)
		to->key_id = NULL;
	else if ((to->key_id = strdup(from->key_id)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	to->valid_after = from->valid_after;
	to->valid_before = from->valid_before;
	if (from->signature_key == NULL)
		to->signature_key = NULL;
	else if ((ret = sshkey_from_private(from->signature_key,
	    &to->signature_key)) != 0)
		return ret;

	if (from->nprincipals > SSHKEY_CERT_MAX_PRINCIPALS)
		return SSH_ERR_INVALID_ARGUMENT;
	if (from->nprincipals > 0) {
		if ((to->principals = calloc(from->nprincipals,
		    sizeof(*to->principals))) == NULL)
			return SSH_ERR_ALLOC_FAIL;
		for (i = 0; i < from->nprincipals; i++) {
			to->principals[i] = strdup(from->principals[i]);
			if (to->principals[i] == NULL) {
				to->nprincipals = i;
				return SSH_ERR_ALLOC_FAIL;
			}
		}
	}
	to->nprincipals = from->nprincipals;
	return 0;
}