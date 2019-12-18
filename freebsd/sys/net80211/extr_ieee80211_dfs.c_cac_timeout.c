#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {scalar_t__ iv_state; int /*<<< orphan*/  iv_ifp; int /*<<< orphan*/  iv_des_chan; struct ieee80211com* iv_ic; } ;
struct ieee80211_dfs_state {int /*<<< orphan*/  newchan; } ;
struct ieee80211com {int ic_nchans; TYPE_1__* ic_curchan; struct ieee80211_channel* ic_channels; struct ieee80211_dfs_state ic_dfs; } ;
struct ieee80211_channel {int /*<<< orphan*/  ic_state; int /*<<< orphan*/  ic_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  ic_freq; int /*<<< orphan*/  ic_ieee; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANSTATE_CACDONE ; 
 scalar_t__ IEEE80211_IS_CHAN_RADAR (TYPE_1__*) ; 
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_NOTIFY_CAC_EXPIRE ; 
 int /*<<< orphan*/  IEEE80211_NOTIFY_CAC_RADAR ; 
 scalar_t__ IEEE80211_S_CAC ; 
 int /*<<< orphan*/  IEEE80211_S_SCAN ; 
 int /*<<< orphan*/  ieee80211_cac_completeswitch (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_new_state_locked (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_notify_cac (struct ieee80211com*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cac_timeout(void *arg)
{
	struct ieee80211vap *vap = arg;
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_dfs_state *dfs = &ic->ic_dfs;
	int i;

	IEEE80211_LOCK_ASSERT(ic);

	if (vap->iv_state != IEEE80211_S_CAC)	/* NB: just in case */
		return;
	/*
	 * When radar is detected during a CAC we are woken
	 * up prematurely to switch to a new channel.
	 * Check the channel to decide how to act.
	 */
	if (IEEE80211_IS_CHAN_RADAR(ic->ic_curchan)) {
		ieee80211_notify_cac(ic, ic->ic_curchan,
		    IEEE80211_NOTIFY_CAC_RADAR);

		if_printf(vap->iv_ifp,
		    "CAC timer on channel %u (%u MHz) stopped due to radar\n",
		    ic->ic_curchan->ic_ieee, ic->ic_curchan->ic_freq);

		/* XXX clobbers any existing desired channel */
		/* NB: dfs->newchan may be NULL, that's ok */
		vap->iv_des_chan = dfs->newchan;
		ieee80211_new_state_locked(vap, IEEE80211_S_SCAN, 0);
	} else {
		if_printf(vap->iv_ifp,
		    "CAC timer on channel %u (%u MHz) expired; "
		    "no radar detected\n",
		    ic->ic_curchan->ic_ieee, ic->ic_curchan->ic_freq);
		/*
		 * Mark all channels with the current frequency
		 * as having completed CAC; this keeps us from
		 * doing it again until we change channels.
		 */
		for (i = 0; i < ic->ic_nchans; i++) {
			struct ieee80211_channel *c = &ic->ic_channels[i];
			if (c->ic_freq == ic->ic_curchan->ic_freq)
				c->ic_state |= IEEE80211_CHANSTATE_CACDONE;
		}
		ieee80211_notify_cac(ic, ic->ic_curchan,
		    IEEE80211_NOTIFY_CAC_EXPIRE);
		ieee80211_cac_completeswitch(vap);
	}
}