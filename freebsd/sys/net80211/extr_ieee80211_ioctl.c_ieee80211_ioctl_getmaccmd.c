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
struct ieee80211vap {struct ieee80211_aclator* iv_acl; } ;
struct ieee80211req {int dummy; } ;
struct ieee80211_aclator {int (* iac_getioctl ) (struct ieee80211vap*,struct ieee80211req*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct ieee80211vap*,struct ieee80211req*) ; 

__attribute__((used)) static int
ieee80211_ioctl_getmaccmd(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	const struct ieee80211_aclator *acl = vap->iv_acl;

	return (acl == NULL ? EINVAL : acl->iac_getioctl(vap, ireq));
}