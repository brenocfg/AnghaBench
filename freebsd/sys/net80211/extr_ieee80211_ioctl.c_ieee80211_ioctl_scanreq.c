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
struct ieee80211vap {int dummy; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211_scan_req {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IEEE80211_FREE (struct ieee80211_scan_req*,int /*<<< orphan*/ ) ; 
 struct ieee80211_scan_req* IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int copyin (int /*<<< orphan*/ ,struct ieee80211_scan_req*,int) ; 
 int ieee80211_scanreq (struct ieee80211vap*,struct ieee80211_scan_req*) ; 

__attribute__((used)) static int
ieee80211_ioctl_scanreq(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211_scan_req *sr;
	int error;

	if (ireq->i_len != sizeof(*sr))
		return EINVAL;
	sr = IEEE80211_MALLOC(sizeof(*sr), M_TEMP,
	     IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
	if (sr == NULL)
		return ENOMEM;
	error = copyin(ireq->i_data, sr, sizeof(*sr));
	if (error != 0)
		goto bad;
	error = ieee80211_scanreq(vap, sr);
bad:
	IEEE80211_FREE(sr, M_TEMP);
	return error;
}