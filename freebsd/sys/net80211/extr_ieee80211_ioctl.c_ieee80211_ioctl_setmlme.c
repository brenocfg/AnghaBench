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
struct ieee80211vap {scalar_t__ iv_opmode; TYPE_1__* iv_des_ssid; } ;
struct ieee80211req_mlme {scalar_t__ im_op; int /*<<< orphan*/  im_reason; int /*<<< orphan*/  im_macaddr; int /*<<< orphan*/  im_ssid; int /*<<< orphan*/  im_ssid_len; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
typedef  int /*<<< orphan*/  mlme ;
struct TYPE_2__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IEEE80211_MLME_ASSOC ; 
 scalar_t__ IEEE80211_M_AHDEMO ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_STA ; 
 int copyin (int /*<<< orphan*/ ,struct ieee80211req_mlme*,int) ; 
 int setmlme_assoc_adhoc (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setmlme_assoc_sta (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setmlme_common (struct ieee80211vap*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ieee80211_ioctl_setmlme(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211req_mlme mlme;
	int error;

	if (ireq->i_len != sizeof(mlme))
		return EINVAL;
	error = copyin(ireq->i_data, &mlme, sizeof(mlme));
	if (error)
		return error;
	if  (vap->iv_opmode == IEEE80211_M_STA &&
	    mlme.im_op == IEEE80211_MLME_ASSOC)
		return setmlme_assoc_sta(vap, mlme.im_macaddr,
		    vap->iv_des_ssid[0].len, vap->iv_des_ssid[0].ssid);
	else if ((vap->iv_opmode == IEEE80211_M_IBSS || 
	    vap->iv_opmode == IEEE80211_M_AHDEMO) && 
	    mlme.im_op == IEEE80211_MLME_ASSOC)
		return setmlme_assoc_adhoc(vap, mlme.im_macaddr,
		    mlme.im_ssid_len, mlme.im_ssid);
	else
		return setmlme_common(vap, mlme.im_op,
		    mlme.im_macaddr, mlme.im_reason);
}