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
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211com {int /*<<< orphan*/  ic_regdomain; } ;

/* Variables and functions */
 int EINVAL ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_getregdomain(struct ieee80211vap *vap,
	const struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;

	if (ireq->i_len != sizeof(ic->ic_regdomain))
		return EINVAL;
	return copyout(&ic->ic_regdomain, ireq->i_data,
	    sizeof(ic->ic_regdomain));
}