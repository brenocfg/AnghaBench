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
struct ieee80211vap {struct ieee80211_aclator const* iv_acl; } ;
struct ieee80211req {int i_val; } ;
typedef  struct ieee80211_aclator {int (* iac_setioctl ) (struct ieee80211vap*,struct ieee80211req*) ;int /*<<< orphan*/  (* iac_detach ) (struct ieee80211vap*) ;int /*<<< orphan*/  (* iac_flush ) (struct ieee80211vap*) ;int /*<<< orphan*/  (* iac_setpolicy ) (struct ieee80211vap*,int) ;int /*<<< orphan*/  (* iac_attach ) (struct ieee80211vap*) ;} const ieee80211_aclator ;

/* Variables and functions */
 int EINVAL ; 
#define  IEEE80211_MACCMD_DETACH 133 
#define  IEEE80211_MACCMD_FLUSH 132 
#define  IEEE80211_MACCMD_POLICY_ALLOW 131 
#define  IEEE80211_MACCMD_POLICY_DENY 130 
#define  IEEE80211_MACCMD_POLICY_OPEN 129 
#define  IEEE80211_MACCMD_POLICY_RADIUS 128 
 struct ieee80211_aclator const* ieee80211_aclator_get (char*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211vap*,int) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211vap*) ; 
 int stub5 (struct ieee80211vap*,struct ieee80211req*) ; 

__attribute__((used)) static int
ieee80211_ioctl_setmaccmd(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	const struct ieee80211_aclator *acl = vap->iv_acl;

	switch (ireq->i_val) {
	case IEEE80211_MACCMD_POLICY_OPEN:
	case IEEE80211_MACCMD_POLICY_ALLOW:
	case IEEE80211_MACCMD_POLICY_DENY:
	case IEEE80211_MACCMD_POLICY_RADIUS:
		if (acl == NULL) {
			acl = ieee80211_aclator_get("mac");
			if (acl == NULL || !acl->iac_attach(vap))
				return EINVAL;
			vap->iv_acl = acl;
		}
		acl->iac_setpolicy(vap, ireq->i_val);
		break;
	case IEEE80211_MACCMD_FLUSH:
		if (acl != NULL)
			acl->iac_flush(vap);
		/* NB: silently ignore when not in use */
		break;
	case IEEE80211_MACCMD_DETACH:
		if (acl != NULL) {
			vap->iv_acl = NULL;
			acl->iac_detach(vap);
		}
		break;
	default:
		if (acl == NULL)
			return EINVAL;
		else
			return acl->iac_setioctl(vap, ireq);
	}
	return 0;
}