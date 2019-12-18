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
struct aclstate {int /*<<< orphan*/  as_list; } ;
struct acl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LOCK (struct aclstate*) ; 
 int /*<<< orphan*/  ACL_UNLOCK (struct aclstate*) ; 
 int /*<<< orphan*/  IEEE80211_DPRINTF (struct ieee80211vap*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_MSG_ACL ; 
 struct acl* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _acl_free (struct aclstate*,struct acl*) ; 

__attribute__((used)) static int
acl_free_all(struct ieee80211vap *vap)
{
	struct aclstate *as = vap->iv_as;
	struct acl *acl;

	IEEE80211_DPRINTF(vap, IEEE80211_MSG_ACL, "ACL: %s\n", "free all");

	ACL_LOCK(as);
	while ((acl = TAILQ_FIRST(&as->as_list)) != NULL)
		_acl_free(as, acl);
	ACL_UNLOCK(as);

	return 0;
}