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
struct aclstate {int /*<<< orphan*/  as_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_POLICY_ALLOW ; 
 int /*<<< orphan*/  ACL_POLICY_DENY ; 
 int /*<<< orphan*/  ACL_POLICY_OPEN ; 
 int /*<<< orphan*/  ACL_POLICY_RADIUS ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_DPRINTF (struct ieee80211vap*,int /*<<< orphan*/ ,char*,int) ; 
#define  IEEE80211_MACCMD_POLICY_ALLOW 131 
#define  IEEE80211_MACCMD_POLICY_DENY 130 
#define  IEEE80211_MACCMD_POLICY_OPEN 129 
#define  IEEE80211_MACCMD_POLICY_RADIUS 128 
 int /*<<< orphan*/  IEEE80211_MSG_ACL ; 

__attribute__((used)) static int
acl_setpolicy(struct ieee80211vap *vap, int policy)
{
	struct aclstate *as = vap->iv_as;

	IEEE80211_DPRINTF(vap, IEEE80211_MSG_ACL,
		"ACL: set policy to %u\n", policy);

	switch (policy) {
	case IEEE80211_MACCMD_POLICY_OPEN:
		as->as_policy = ACL_POLICY_OPEN;
		break;
	case IEEE80211_MACCMD_POLICY_ALLOW:
		as->as_policy = ACL_POLICY_ALLOW;
		break;
	case IEEE80211_MACCMD_POLICY_DENY:
		as->as_policy = ACL_POLICY_DENY;
		break;
	case IEEE80211_MACCMD_POLICY_RADIUS:
		as->as_policy = ACL_POLICY_RADIUS;
		break;
	default:
		return EINVAL;
	}
	return 0;
}