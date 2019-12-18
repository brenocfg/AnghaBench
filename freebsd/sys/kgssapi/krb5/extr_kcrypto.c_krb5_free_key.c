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
struct krb5_key_state {struct krb5_key_state* ks_key; TYPE_1__* ks_class; int /*<<< orphan*/  ks_refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ec_keylen; int /*<<< orphan*/  (* ec_destroy ) (struct krb5_key_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  bzero (struct krb5_key_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct krb5_key_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct krb5_key_state*) ; 

void
krb5_free_key(struct krb5_key_state *ks)
{

	if (refcount_release(&ks->ks_refs)) {
		ks->ks_class->ec_destroy(ks);
		bzero(ks->ks_key, ks->ks_class->ec_keylen);
		free(ks->ks_key, M_GSSAPI);
		free(ks, M_GSSAPI);
	}
}