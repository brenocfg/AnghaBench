#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sshkey {scalar_t__ type; } ;
struct ssh {TYPE_1__* kex; } ;
struct TYPE_4__ {char* pubkey_key_types; } ;
struct TYPE_3__ {char* server_sig_algs; } ;

/* Variables and functions */
 scalar_t__ KEY_RSA ; 
 scalar_t__ KEY_RSA_CERT ; 
 int /*<<< orphan*/  free (char*) ; 
 char* match_list (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  sshkey_sigalg_by_name (char*) ; 
 int /*<<< orphan*/  sshkey_ssh_name (struct sshkey const*) ; 
 scalar_t__ sshkey_type_from_name (char*) ; 
 char* strsep (char**,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
key_sig_algorithm(struct ssh *ssh, const struct sshkey *key)
{
	char *allowed, *oallowed, *cp, *tmp, *alg = NULL;

	/*
	 * The signature algorithm will only differ from the key algorithm
	 * for RSA keys/certs and when the server advertises support for
	 * newer (SHA2) algorithms.
	 */
	if (ssh == NULL || ssh->kex->server_sig_algs == NULL ||
	    (key->type != KEY_RSA && key->type != KEY_RSA_CERT)) {
		/* Filter base key signature alg against our configuration */
		return match_list(sshkey_ssh_name(key),
		    options.pubkey_key_types, NULL);
	}

	/*
	 * For RSA keys/certs, since these might have a different sig type:
	 * find the first entry in PubkeyAcceptedKeyTypes of the right type
	 * that also appears in the supported signature algorithms list from
	 * the server.
	 */
	oallowed = allowed = xstrdup(options.pubkey_key_types);
	while ((cp = strsep(&allowed, ",")) != NULL) {
		if (sshkey_type_from_name(cp) != key->type)
			continue;
		tmp = match_list(sshkey_sigalg_by_name(cp), ssh->kex->server_sig_algs, NULL);
		if (tmp != NULL)
			alg = xstrdup(cp);
		free(tmp);
		if (alg != NULL)
			break;
	}
	free(oallowed);
	return alg;
}