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
struct ieee80211vap {scalar_t__ iv_opmode; struct ieee80211_hwmp_state* iv_hwmp; } ;
struct ieee80211req {int i_type; int i_val; } ;
struct ieee80211_hwmp_state {int hs_rootmode; int hs_maxhops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  IEEE80211_IOC_HWMP_MAXHOPS 129 
#define  IEEE80211_IOC_HWMP_ROOTMODE 128 
 scalar_t__ IEEE80211_M_MBSS ; 
 int /*<<< orphan*/  hwmp_rootmode_setup (struct ieee80211vap*) ; 

__attribute__((used)) static int
hwmp_ioctl_set80211(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211_hwmp_state *hs = vap->iv_hwmp;
	int error;

	if (vap->iv_opmode != IEEE80211_M_MBSS)
		return ENOSYS;
	error = 0;
	switch (ireq->i_type) {
	case IEEE80211_IOC_HWMP_ROOTMODE:
		if (ireq->i_val < 0 || ireq->i_val > 3)
			return EINVAL;
		hs->hs_rootmode = ireq->i_val;
		hwmp_rootmode_setup(vap);
		break;
	case IEEE80211_IOC_HWMP_MAXHOPS:
		if (ireq->i_val <= 0 || ireq->i_val > 255)
			return EINVAL;
		hs->hs_maxhops = ireq->i_val;
		break;
	default:
		return ENOSYS;
	}
	return error;
}