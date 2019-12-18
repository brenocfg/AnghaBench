#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wmeParams {int wmep_logcwmin; int wmep_logcwmax; int wmep_aifsn; int wmep_txopLimit; int wmep_acm; int /*<<< orphan*/  wmep_noackPolicy; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211req {int i_len; int i_type; int i_val; } ;
struct TYPE_4__ {struct wmeParams* cap_wmeParams; } ;
struct TYPE_3__ {struct wmeParams* cap_wmeParams; } ;
struct ieee80211_wme_state {TYPE_2__ wme_wmeChanParams; TYPE_1__ wme_wmeBssChanParams; } ;
struct ieee80211com {int ic_caps; struct ieee80211_wme_state ic_wme; } ;

/* Variables and functions */
 int EINVAL ; 
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
 int WME_NUM_AC ; 

__attribute__((used)) static int
ieee80211_ioctl_getwmeparam(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_wme_state *wme = &ic->ic_wme;
	struct wmeParams *wmep;
	int ac;

	if ((ic->ic_caps & IEEE80211_C_WME) == 0)
		return EINVAL;

	ac = (ireq->i_len & IEEE80211_WMEPARAM_VAL);
	if (ac >= WME_NUM_AC)
		ac = WME_AC_BE;
	if (ireq->i_len & IEEE80211_WMEPARAM_BSS)
		wmep = &wme->wme_wmeBssChanParams.cap_wmeParams[ac];
	else
		wmep = &wme->wme_wmeChanParams.cap_wmeParams[ac];
	switch (ireq->i_type) {
	case IEEE80211_IOC_WME_CWMIN:		/* WME: CWmin */
		ireq->i_val = wmep->wmep_logcwmin;
		break;
	case IEEE80211_IOC_WME_CWMAX:		/* WME: CWmax */
		ireq->i_val = wmep->wmep_logcwmax;
		break;
	case IEEE80211_IOC_WME_AIFS:		/* WME: AIFS */
		ireq->i_val = wmep->wmep_aifsn;
		break;
	case IEEE80211_IOC_WME_TXOPLIMIT:	/* WME: txops limit */
		ireq->i_val = wmep->wmep_txopLimit;
		break;
	case IEEE80211_IOC_WME_ACM:		/* WME: ACM (bss only) */
		wmep = &wme->wme_wmeBssChanParams.cap_wmeParams[ac];
		ireq->i_val = wmep->wmep_acm;
		break;
	case IEEE80211_IOC_WME_ACKPOLICY:	/* WME: ACK policy (!bss only)*/
		wmep = &wme->wme_wmeChanParams.cap_wmeParams[ac];
		ireq->i_val = !wmep->wmep_noackPolicy;
		break;
	}
	return 0;
}