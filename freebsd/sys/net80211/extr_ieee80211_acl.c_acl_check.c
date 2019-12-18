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
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; } ;
struct aclstate {int as_policy; } ;

/* Variables and functions */
#define  ACL_POLICY_ALLOW 131 
#define  ACL_POLICY_DENY 130 
#define  ACL_POLICY_OPEN 129 
#define  ACL_POLICY_RADIUS 128 
 int /*<<< orphan*/ * _find_acl (struct aclstate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acl_check(struct ieee80211vap *vap, const struct ieee80211_frame *wh)
{
	struct aclstate *as = vap->iv_as;

	switch (as->as_policy) {
	case ACL_POLICY_OPEN:
	case ACL_POLICY_RADIUS:
		return 1;
	case ACL_POLICY_ALLOW:
		return _find_acl(as, wh->i_addr2) != NULL;
	case ACL_POLICY_DENY:
		return _find_acl(as, wh->i_addr2) == NULL;
	}
	return 0;		/* should not happen */
}