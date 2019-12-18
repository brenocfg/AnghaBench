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
struct aclstate {struct ieee80211vap* as_vap; int /*<<< orphan*/  as_policy; int /*<<< orphan*/  as_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LOCK_INIT (struct aclstate*,char*) ; 
 int /*<<< orphan*/  ACL_POLICY_OPEN ; 
 scalar_t__ IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  M_80211_ACL ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nrefs ; 

__attribute__((used)) static int
acl_attach(struct ieee80211vap *vap)
{
	struct aclstate *as;

	as = (struct aclstate *) IEEE80211_MALLOC(sizeof(struct aclstate),
		M_80211_ACL, IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
	if (as == NULL)
		return 0;
	ACL_LOCK_INIT(as, "acl");
	TAILQ_INIT(&as->as_list);
	as->as_policy = ACL_POLICY_OPEN;
	as->as_vap = vap;
	vap->iv_as = as;
	nrefs++;			/* NB: we assume caller locking */
	return 1;
}