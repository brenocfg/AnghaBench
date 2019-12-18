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
struct secasvar {scalar_t__ state; scalar_t__ refcnt; int flags; int /*<<< orphan*/  lft_c; struct secasvar* lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPSEC_MISC ; 
 int /*<<< orphan*/  M_IPSEC_SA ; 
 scalar_t__ SADB_SASTATE_DEAD ; 
 int SADB_X_EXT_F_CLONED ; 
 int /*<<< orphan*/  V_key_lft_zone ; 
 int /*<<< orphan*/  free (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_cleansav (struct secasvar*) ; 
 int /*<<< orphan*/  mtx_destroy (struct secasvar*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
key_delsav(struct secasvar *sav)
{
	IPSEC_ASSERT(sav != NULL, ("null sav"));
	IPSEC_ASSERT(sav->state == SADB_SASTATE_DEAD,
	    ("attempt to free non DEAD SA %p", sav));
	IPSEC_ASSERT(sav->refcnt == 0, ("reference count %u > 0",
	    sav->refcnt));

	/*
	 * SA must be unlinked from the chain and hashtbl.
	 * If SA was cloned, we leave all fields untouched,
	 * except NAT-T config.
	 */
	key_cleansav(sav);
	if ((sav->flags & SADB_X_EXT_F_CLONED) == 0) {
		mtx_destroy(sav->lock);
		free(sav->lock, M_IPSEC_MISC);
		uma_zfree(V_key_lft_zone, sav->lft_c);
	}
	free(sav, M_IPSEC_SA);
}