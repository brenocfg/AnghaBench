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
struct krb5_key_state {struct aes_state* ks_priv; } ;
struct aes_state {scalar_t__ as_session_aes; scalar_t__ as_session_sha1; int /*<<< orphan*/  as_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  crypto_freesession (scalar_t__) ; 
 int /*<<< orphan*/  free (struct aes_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aes_destroy(struct krb5_key_state *ks)
{
	struct aes_state *as = ks->ks_priv;

	if (as->as_session_aes != 0)
		crypto_freesession(as->as_session_aes);
	if (as->as_session_sha1 != 0)
		crypto_freesession(as->as_session_sha1);
	mtx_destroy(&as->as_lock);
	free(ks->ks_priv, M_GSSAPI);
}