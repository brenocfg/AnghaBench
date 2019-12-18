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
struct ieee80211vap {TYPE_1__* iv_ic; } ;
struct ieee80211req_wpaie2 {int /*<<< orphan*/  wpa_ie; int /*<<< orphan*/  rsn_ie; int /*<<< orphan*/  wpa_macaddr; } ;
struct ieee80211req_wpaie {int dummy; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct TYPE_4__ {int* wpa_ie; int* rsn_ie; } ;
struct ieee80211_node {TYPE_2__ ni_ies; } ;
struct TYPE_3__ {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_FREE (struct ieee80211req_wpaie2*,int /*<<< orphan*/ ) ; 
 int IEEE80211_IOC_WPAIE2 ; 
 struct ieee80211req_wpaie2* IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int copyout (struct ieee80211req_wpaie2*,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_node* ieee80211_find_vap_node (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_getwpaie(struct ieee80211vap *vap,
	struct ieee80211req *ireq, int req)
{
	struct ieee80211_node *ni;
	struct ieee80211req_wpaie2 *wpaie;
	int error;

	if (ireq->i_len < IEEE80211_ADDR_LEN)
		return EINVAL;
	wpaie = IEEE80211_MALLOC(sizeof(*wpaie), M_TEMP,
	    IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
	if (wpaie == NULL)
		return ENOMEM;
	error = copyin(ireq->i_data, wpaie->wpa_macaddr, IEEE80211_ADDR_LEN);
	if (error != 0)
		goto bad;
	ni = ieee80211_find_vap_node(&vap->iv_ic->ic_sta, vap, wpaie->wpa_macaddr);
	if (ni == NULL) {
		error = ENOENT;
		goto bad;
	}
	if (ni->ni_ies.wpa_ie != NULL) {
		int ielen = ni->ni_ies.wpa_ie[1] + 2;
		if (ielen > sizeof(wpaie->wpa_ie))
			ielen = sizeof(wpaie->wpa_ie);
		memcpy(wpaie->wpa_ie, ni->ni_ies.wpa_ie, ielen);
	}
	if (req == IEEE80211_IOC_WPAIE2) {
		if (ni->ni_ies.rsn_ie != NULL) {
			int ielen = ni->ni_ies.rsn_ie[1] + 2;
			if (ielen > sizeof(wpaie->rsn_ie))
				ielen = sizeof(wpaie->rsn_ie);
			memcpy(wpaie->rsn_ie, ni->ni_ies.rsn_ie, ielen);
		}
		if (ireq->i_len > sizeof(struct ieee80211req_wpaie2))
			ireq->i_len = sizeof(struct ieee80211req_wpaie2);
	} else {
		/* compatibility op, may overwrite wpa ie */
		/* XXX check ic_flags? */
		if (ni->ni_ies.rsn_ie != NULL) {
			int ielen = ni->ni_ies.rsn_ie[1] + 2;
			if (ielen > sizeof(wpaie->wpa_ie))
				ielen = sizeof(wpaie->wpa_ie);
			memcpy(wpaie->wpa_ie, ni->ni_ies.rsn_ie, ielen);
		}
		if (ireq->i_len > sizeof(struct ieee80211req_wpaie))
			ireq->i_len = sizeof(struct ieee80211req_wpaie);
	}
	ieee80211_free_node(ni);
	error = copyout(wpaie, ireq->i_data, ireq->i_len);
bad:
	IEEE80211_FREE(wpaie, M_TEMP);
	return error;
}