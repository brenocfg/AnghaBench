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
struct ucred {int cr_ref; scalar_t__ cr_groups; scalar_t__ cr_smallgroups; int /*<<< orphan*/ * cr_loginclass; int /*<<< orphan*/ * cr_prison; int /*<<< orphan*/ * cr_ruidinfo; int /*<<< orphan*/ * cr_uidinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CRED ; 
 int /*<<< orphan*/  audit_cred_destroy (struct ucred*) ; 
 int /*<<< orphan*/  free (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loginclass_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_cred_destroy (struct ucred*) ; 
 int /*<<< orphan*/  prison_free (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int*) ; 
 int /*<<< orphan*/  uifree (int /*<<< orphan*/ *) ; 

void
crfree(struct ucred *cr)
{

	KASSERT(cr->cr_ref > 0, ("bad ucred refcount: %d", cr->cr_ref));
	KASSERT(cr->cr_ref != 0xdeadc0de, ("dangling reference to ucred"));
	if (refcount_release(&cr->cr_ref)) {
		/*
		 * Some callers of crget(), such as nfs_statfs(),
		 * allocate a temporary credential, but don't
		 * allocate a uidinfo structure.
		 */
		if (cr->cr_uidinfo != NULL)
			uifree(cr->cr_uidinfo);
		if (cr->cr_ruidinfo != NULL)
			uifree(cr->cr_ruidinfo);
		/*
		 * Free a prison, if any.
		 */
		if (cr->cr_prison != NULL)
			prison_free(cr->cr_prison);
		if (cr->cr_loginclass != NULL)
			loginclass_free(cr->cr_loginclass);
#ifdef AUDIT
		audit_cred_destroy(cr);
#endif
#ifdef MAC
		mac_cred_destroy(cr);
#endif
		if (cr->cr_groups != cr->cr_smallgroups)
			free(cr->cr_groups, M_CRED);
		free(cr, M_CRED);
	}
}