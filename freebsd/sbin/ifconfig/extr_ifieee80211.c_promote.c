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
struct TYPE_2__ {int /*<<< orphan*/  ifm_current; } ;

/* Variables and functions */
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_G ; 
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IFM_AUTO ; 
 int IFM_IEEE80211_11A ; 
 int IFM_IEEE80211_11B ; 
 int IFM_IEEE80211_11G ; 
 int IFM_MODE (int /*<<< orphan*/ ) ; 
 int canpromote (int,int,int) ; 
 int htconf ; 
 TYPE_1__* ifmr ; 

__attribute__((used)) static int
promote(int i)
{
	/*
	 * Query the current mode of the interface in case it's
	 * constrained (e.g. to 11a).  We must do this carefully
	 * as there may be a pending ifmedia request in which case
	 * asking the kernel will give us the wrong answer.  This
	 * is an unfortunate side-effect of the way ifconfig is
	 * structure for modularity (yech).
	 *
	 * NB: ifmr is actually setup in getchaninfo (above); we
	 *     assume it's called coincident with to this call so
	 *     we have a ``current setting''; otherwise we must pass
	 *     the socket descriptor down to here so we can make
	 *     the ifmedia_getstate call ourselves.
	 */
	int chanmode = ifmr != NULL ? IFM_MODE(ifmr->ifm_current) : IFM_AUTO;

	/* when ambiguous promote to ``best'' */
	/* NB: we abitrarily pick HT40+ over HT40- */
	if (chanmode != IFM_IEEE80211_11B)
		i = canpromote(i, IEEE80211_CHAN_B, IEEE80211_CHAN_G);
	if (chanmode != IFM_IEEE80211_11G && (htconf & 1)) {
		i = canpromote(i, IEEE80211_CHAN_G,
			IEEE80211_CHAN_G | IEEE80211_CHAN_HT20);
		if (htconf & 2) {
			i = canpromote(i, IEEE80211_CHAN_G,
				IEEE80211_CHAN_G | IEEE80211_CHAN_HT40D);
			i = canpromote(i, IEEE80211_CHAN_G,
				IEEE80211_CHAN_G | IEEE80211_CHAN_HT40U);
		}
	}
	if (chanmode != IFM_IEEE80211_11A && (htconf & 1)) {
		i = canpromote(i, IEEE80211_CHAN_A,
			IEEE80211_CHAN_A | IEEE80211_CHAN_HT20);
		if (htconf & 2) {
			i = canpromote(i, IEEE80211_CHAN_A,
				IEEE80211_CHAN_A | IEEE80211_CHAN_HT40D);
			i = canpromote(i, IEEE80211_CHAN_A,
				IEEE80211_CHAN_A | IEEE80211_CHAN_HT40U);
		}
	}
	return i;
}