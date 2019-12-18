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
struct ieee80211vap {struct aclstate* iv_as; } ;
struct aclstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LOCK_DESTROY (struct aclstate*) ; 
 int /*<<< orphan*/  IEEE80211_FREE (struct aclstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_80211_ACL ; 
 int /*<<< orphan*/  acl_free_all (struct ieee80211vap*) ; 
 scalar_t__ nrefs ; 

__attribute__((used)) static void
acl_detach(struct ieee80211vap *vap)
{
	struct aclstate *as = vap->iv_as;

	KASSERT(nrefs > 0, ("imbalanced attach/detach"));
	nrefs--;			/* NB: we assume caller locking */

	acl_free_all(vap);
	vap->iv_as = NULL;
	ACL_LOCK_DESTROY(as);
	IEEE80211_FREE(as, M_80211_ACL);
}