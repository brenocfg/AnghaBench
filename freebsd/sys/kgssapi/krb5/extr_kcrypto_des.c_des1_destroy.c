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
struct krb5_key_state {struct des1_state* ks_priv; } ;
struct des1_state {int /*<<< orphan*/  ds_lock; scalar_t__ ds_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  crypto_freesession (scalar_t__) ; 
 int /*<<< orphan*/  free (struct des1_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
des1_destroy(struct krb5_key_state *ks)
{
	struct des1_state *ds = ks->ks_priv;

	if (ds->ds_session)
		crypto_freesession(ds->ds_session);
	mtx_destroy(&ds->ds_lock);
	free(ks->ks_priv, M_GSSAPI);

}