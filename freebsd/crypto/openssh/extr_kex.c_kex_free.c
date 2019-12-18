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
struct kex {struct kex* name; struct kex* hostkey_alg; struct kex* failed_choice; struct kex* server_version_string; struct kex* client_version_string; struct kex* session_id; int /*<<< orphan*/  my; int /*<<< orphan*/  peer; int /*<<< orphan*/ ** newkeys; int /*<<< orphan*/  ec_client_key; int /*<<< orphan*/  dh; } ;

/* Variables and functions */
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ ) ; 
 size_t MODE_MAX ; 
 int /*<<< orphan*/  free (struct kex*) ; 
 int /*<<< orphan*/  kex_free_newkeys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_free (int /*<<< orphan*/ ) ; 

void
kex_free(struct kex *kex)
{
	u_int mode;

#ifdef WITH_OPENSSL
	DH_free(kex->dh);
#ifdef OPENSSL_HAS_ECC
	EC_KEY_free(kex->ec_client_key);
#endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */
	for (mode = 0; mode < MODE_MAX; mode++) {
		kex_free_newkeys(kex->newkeys[mode]);
		kex->newkeys[mode] = NULL;
	}
	sshbuf_free(kex->peer);
	sshbuf_free(kex->my);
	free(kex->session_id);
	free(kex->client_version_string);
	free(kex->server_version_string);
	free(kex->failed_choice);
	free(kex->hostkey_alg);
	free(kex->name);
	free(kex);
}