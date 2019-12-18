#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wmeParams {int wmep_noackPolicy; int /*<<< orphan*/  wmep_acm; int /*<<< orphan*/  wmep_txopLimit; int /*<<< orphan*/  wmep_aifsn; int /*<<< orphan*/  wmep_logcwmax; int /*<<< orphan*/  wmep_logcwmin; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211req {int i_len; int i_type; int /*<<< orphan*/  i_val; } ;
struct TYPE_8__ {struct wmeParams* cap_wmeParams; } ;
struct TYPE_7__ {struct wmeParams* cap_wmeParams; } ;
struct TYPE_6__ {struct wmeParams* cap_wmeParams; } ;
struct TYPE_5__ {struct wmeParams* cap_wmeParams; } ;
struct ieee80211_wme_state {int wme_flags; TYPE_4__ wme_wmeChanParams; TYPE_3__ wme_chanParams; TYPE_2__ wme_wmeBssChanParams; TYPE_1__ wme_bssChanParams; } ;
struct ieee80211com {int ic_caps; struct ieee80211_wme_state ic_wme; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IEEE80211_C_WME ; 
#define  IEEE80211_IOC_WME_ACKPOLICY 133 
#define  IEEE80211_IOC_WME_ACM 132 
#define  IEEE80211_IOC_WME_AIFS 131 
#define  IEEE80211_IOC_WME_CWMAX 130 
#define  IEEE80211_IOC_WME_CWMIN 129 
#define  IEEE80211_IOC_WME_TXOPLIMIT 128 
 int IEEE80211_WMEPARAM_BSS ; 
 int IEEE80211_WMEPARAM_VAL ; 
 int WME_AC_BE ; 
 int WME_F_AGGRMODE ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/  ieee80211_wme_updateparams (struct ieee80211vap*) ; 

__attribute__((used)) static int
ieee80211_ioctl_setwmeparam(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_wme_state *wme = &ic->ic_wme;
	struct wmeParams *wmep, *chanp;
	int isbss, ac, aggrmode;

	if ((ic->ic_caps & IEEE80211_C_WME) == 0)
		return EOPNOTSUPP;

	isbss = (ireq->i_len & IEEE80211_WMEPARAM_BSS);
	ac = (ireq->i_len & IEEE80211_WMEPARAM_VAL);
	aggrmode = (wme->wme_flags & WME_F_AGGRMODE);
	if (ac >= WME_NUM_AC)
		ac = WME_AC_BE;
	if (isbss) {
		chanp = &wme->wme_bssChanParams.cap_wmeParams[ac];
		wmep = &wme->wme_wmeBssChanParams.cap_wmeParams[ac];
	} else {
		chanp = &wme->wme_chanParams.cap_wmeParams[ac];
		wmep = &wme->wme_wmeChanParams.cap_wmeParams[ac];
	}
	switch (ireq->i_type) {
	case IEEE80211_IOC_WME_CWMIN:		/* WME: CWmin */
		wmep->wmep_logcwmin = ireq->i_val;
		if (!isbss || !aggrmode)
			chanp->wmep_logcwmin = ireq->i_val;
		break;
	case IEEE80211_IOC_WME_CWMAX:		/* WME: CWmax */
		wmep->wmep_logcwmax = ireq->i_val;
		if (!isbss || !aggrmode)
			chanp->wmep_logcwmax = ireq->i_val;
		break;
	case IEEE80211_IOC_WME_AIFS:		/* WME: AIFS */
		wmep->wmep_aifsn = ireq->i_val;
		if (!isbss || !aggrmode)
			chanp->wmep_aifsn = ireq->i_val;
		break;
	case IEEE80211_IOC_WME_TXOPLIMIT:	/* WME: txops limit */
		wmep->wmep_txopLimit = ireq->i_val;
		if (!isbss || !aggrmode)
			chanp->wmep_txopLimit = ireq->i_val;
		break;
	case IEEE80211_IOC_WME_ACM:		/* WME: ACM (bss only) */
		wmep->wmep_acm = ireq->i_val;
		if (!aggrmode)
			chanp->wmep_acm = ireq->i_val;
		break;
	case IEEE80211_IOC_WME_ACKPOLICY:	/* WME: ACK policy (!bss only)*/
		wmep->wmep_noackPolicy = chanp->wmep_noackPolicy =
			(ireq->i_val) == 0;
		break;
	}
	ieee80211_wme_updateparams(vap);
	return 0;
}