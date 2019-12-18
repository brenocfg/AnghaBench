#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sshkey {int dummy; } ;
struct ssh {int /*<<< orphan*/  public_keys; int /*<<< orphan*/  private_keys; TYPE_1__* kex; } ;
struct key_entry {struct sshkey* key; } ;
struct TYPE_2__ {scalar_t__ server; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct key_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct key_entry*) ; 
 struct key_entry* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_from_private (struct sshkey*,struct sshkey**) ; 

int
ssh_add_hostkey(struct ssh *ssh, struct sshkey *key)
{
	struct sshkey *pubkey = NULL;
	struct key_entry *k = NULL, *k_prv = NULL;
	int r;

	if (ssh->kex->server) {
		if ((r = sshkey_from_private(key, &pubkey)) != 0)
			return r;
		if ((k = malloc(sizeof(*k))) == NULL ||
		    (k_prv = malloc(sizeof(*k_prv))) == NULL) {
			free(k);
			sshkey_free(pubkey);
			return SSH_ERR_ALLOC_FAIL;
		}
		k_prv->key = key;
		TAILQ_INSERT_TAIL(&ssh->private_keys, k_prv, next);

		/* add the public key, too */
		k->key = pubkey;
		TAILQ_INSERT_TAIL(&ssh->public_keys, k, next);
		r = 0;
	} else {
		if ((k = malloc(sizeof(*k))) == NULL)
			return SSH_ERR_ALLOC_FAIL;
		k->key = key;
		TAILQ_INSERT_TAIL(&ssh->public_keys, k, next);
		r = 0;
	}

	return r;
}