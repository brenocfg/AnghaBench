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
struct kexalg {int /*<<< orphan*/  ec_nid; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  type; } ;
struct kex {char* name; int /*<<< orphan*/  ec_nid; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  kex_type; } ;

/* Variables and functions */
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_NO_KEX_ALG_MATCH ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 struct kexalg* kex_alg_by_name (char*) ; 
 char* match_list (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
choose_kex(struct kex *k, char *client, char *server)
{
	const struct kexalg *kexalg;

	k->name = match_list(client, server, NULL);

	debug("kex: algorithm: %s", k->name ? k->name : "(no match)");
	if (k->name == NULL)
		return SSH_ERR_NO_KEX_ALG_MATCH;
	if ((kexalg = kex_alg_by_name(k->name)) == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	k->kex_type = kexalg->type;
	k->hash_alg = kexalg->hash_alg;
	k->ec_nid = kexalg->ec_nid;
	return 0;
}