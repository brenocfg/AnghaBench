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
struct nlm_file_svid {scalar_t__ ns_ucred; int /*<<< orphan*/  ns_svid; int /*<<< orphan*/  ns_active; int /*<<< orphan*/  ns_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nlm_file_svid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NLM ; 
 int /*<<< orphan*/  crfree (scalar_t__) ; 
 int /*<<< orphan*/  free (struct nlm_file_svid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_svid_allocator ; 
 int /*<<< orphan*/  nlm_svid_lock ; 
 int /*<<< orphan*/  ns_link ; 

__attribute__((used)) static void
nlm_free_svid(struct nlm_file_svid *ns)
{

	mtx_lock(&nlm_svid_lock);
	ns->ns_refs--;
	if (!ns->ns_refs) {
		KASSERT(!ns->ns_active, ("Freeing active SVID"));
		LIST_REMOVE(ns, ns_link);
		mtx_unlock(&nlm_svid_lock);
		free_unr(nlm_svid_allocator, ns->ns_svid);
		if (ns->ns_ucred)
			crfree(ns->ns_ucred);
		free(ns, M_NLM);
	} else {
		mtx_unlock(&nlm_svid_lock);
	}
}