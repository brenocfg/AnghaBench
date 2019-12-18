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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211com {int ic_nchans; int /*<<< orphan*/  ic_chan_active; TYPE_1__* ic_bsschan; struct ieee80211_channel* ic_channels; } ;
struct ieee80211_channel {int ic_ieee; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_ieee; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETRESET ; 
 int ENOMEM ; 
 TYPE_1__* IEEE80211_CHAN_ANYC ; 
 scalar_t__ IEEE80211_CHAN_BYTES ; 
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IEEE80211_MALLOC (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int NBBY ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_scan_flush (struct ieee80211vap*) ; 
 scalar_t__ isclr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_setchanlist(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;
	uint8_t *chanlist, *list;
	int i, nchan, maxchan, error;

	if (ireq->i_len > sizeof(ic->ic_chan_active))
		ireq->i_len = sizeof(ic->ic_chan_active);
	list = IEEE80211_MALLOC(ireq->i_len + IEEE80211_CHAN_BYTES, M_TEMP,
	    IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
	if (list == NULL)
		return ENOMEM;
	error = copyin(ireq->i_data, list, ireq->i_len);
	if (error) {
		IEEE80211_FREE(list, M_TEMP);
		return error;
	}
	nchan = 0;
	chanlist = list + ireq->i_len;		/* NB: zero'd already */
	maxchan = ireq->i_len * NBBY;
	for (i = 0; i < ic->ic_nchans; i++) {
		const struct ieee80211_channel *c = &ic->ic_channels[i];
		/*
		 * Calculate the intersection of the user list and the
		 * available channels so users can do things like specify
		 * 1-255 to get all available channels.
		 */
		if (c->ic_ieee < maxchan && isset(list, c->ic_ieee)) {
			setbit(chanlist, c->ic_ieee);
			nchan++;
		}
	}
	if (nchan == 0) {
		IEEE80211_FREE(list, M_TEMP);
		return EINVAL;
	}
	if (ic->ic_bsschan != IEEE80211_CHAN_ANYC &&	/* XXX */
	    isclr(chanlist, ic->ic_bsschan->ic_ieee))
		ic->ic_bsschan = IEEE80211_CHAN_ANYC;
	memcpy(ic->ic_chan_active, chanlist, IEEE80211_CHAN_BYTES);
	ieee80211_scan_flush(vap);
	IEEE80211_FREE(list, M_TEMP);
	return ENETRESET;
}