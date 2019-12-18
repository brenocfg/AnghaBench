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
struct ieee80211vap {struct ieee80211_txparam* iv_txparms; struct ieee80211com* iv_ic; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211_htrateset {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_modecaps; struct ieee80211_htrateset ic_sup_htrates; struct ieee80211_rateset* ic_sup_rates; } ;
struct ieee80211_txparams_req {struct ieee80211_txparam* params; } ;
struct ieee80211_txparam {scalar_t__ ucastrate; scalar_t__ mcastrate; scalar_t__ mgmtrate; scalar_t__ maxretry; } ;
struct ieee80211_rateset {int dummy; } ;
typedef  int /*<<< orphan*/  parms ;

/* Variables and functions */
 int EINVAL ; 
 int ENETRESET ; 
 int IEEE80211_MODE_11A ; 
 int IEEE80211_MODE_11NA ; 
 int IEEE80211_MODE_11NG ; 
 int /*<<< orphan*/  checkmcs (struct ieee80211_htrateset const*,scalar_t__) ; 
 int /*<<< orphan*/  checkrate (struct ieee80211_rateset const*,scalar_t__) ; 
 int copyin (int /*<<< orphan*/ ,struct ieee80211_txparams_req*,int) ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isset (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_settxparams(struct ieee80211vap *vap,
	const struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_txparams_req parms;	/* XXX stack use? */
	struct ieee80211_txparam *src, *dst;
	const struct ieee80211_htrateset *rs_ht;
	const struct ieee80211_rateset *rs;
	int error, mode, changed, is11n, nmodes;

	/* NB: accept short requests for backwards compat */
	if (ireq->i_len > sizeof(parms))
		return EINVAL;
	error = copyin(ireq->i_data, &parms, ireq->i_len);
	if (error != 0)
		return error;
	nmodes = ireq->i_len / sizeof(struct ieee80211_txparam);
	changed = 0;
	/* validate parameters and check if anything changed */
	for (mode = IEEE80211_MODE_11A; mode < nmodes; mode++) {
		if (isclr(ic->ic_modecaps, mode))
			continue;
		src = &parms.params[mode];
		dst = &vap->iv_txparms[mode];
		rs = &ic->ic_sup_rates[mode];	/* NB: 11n maps to legacy */
		rs_ht = &ic->ic_sup_htrates;
		is11n = (mode == IEEE80211_MODE_11NA ||
			 mode == IEEE80211_MODE_11NG);
		if (src->ucastrate != dst->ucastrate) {
			if (!checkrate(rs, src->ucastrate) &&
			    (!is11n || !checkmcs(rs_ht, src->ucastrate)))
				return EINVAL;
			changed++;
		}
		if (src->mcastrate != dst->mcastrate) {
			if (!checkrate(rs, src->mcastrate) &&
			    (!is11n || !checkmcs(rs_ht, src->mcastrate)))
				return EINVAL;
			changed++;
		}
		if (src->mgmtrate != dst->mgmtrate) {
			if (!checkrate(rs, src->mgmtrate) &&
			    (!is11n || !checkmcs(rs_ht, src->mgmtrate)))
				return EINVAL;
			changed++;
		}
		if (src->maxretry != dst->maxretry)	/* NB: no bounds */
			changed++;
	}
	if (changed) {
		/*
		 * Copy new parameters in place and notify the
		 * driver so it can push state to the device.
		 */
		for (mode = IEEE80211_MODE_11A; mode < nmodes; mode++) {
			if (isset(ic->ic_modecaps, mode))
				vap->iv_txparms[mode] = parms.params[mode];
		}
		/* XXX could be more intelligent,
		   e.g. don't reset if setting not being used */
		return ENETRESET;
	}
	return 0;
}