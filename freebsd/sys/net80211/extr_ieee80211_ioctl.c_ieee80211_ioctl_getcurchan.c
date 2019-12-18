#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {scalar_t__ iv_state; TYPE_1__* iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211com {struct ieee80211_channel* ic_curchan; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {struct ieee80211_channel* ni_chan; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IEEE80211_S_RUN ; 
 scalar_t__ IEEE80211_S_SLEEP ; 
 int copyout (struct ieee80211_channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_getcurchan(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_channel *c;

	if (ireq->i_len != sizeof(struct ieee80211_channel))
		return EINVAL;
	/*
	 * vap's may have different operating channels when HT is
	 * in use.  When in RUN state report the vap-specific channel.
	 * Otherwise return curchan.
	 */
	if (vap->iv_state == IEEE80211_S_RUN || vap->iv_state == IEEE80211_S_SLEEP)
		c = vap->iv_bss->ni_chan;
	else
		c = ic->ic_curchan;
	return copyout(c, ireq->i_data, sizeof(*c));
}