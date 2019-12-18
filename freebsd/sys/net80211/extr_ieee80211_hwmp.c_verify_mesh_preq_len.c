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
typedef  int uint8_t ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DISCARD (struct ieee80211vap*,int,struct ieee80211_frame const*,int /*<<< orphan*/ *,char*,char*) ; 
 int IEEE80211_MESHPREQ_BASE_SZ ; 
 int IEEE80211_MESHPREQ_BASE_SZ_AE ; 
 int const IEEE80211_MESHPREQ_FLAGS_AE ; 
 size_t IEEE80211_MESHPREQ_TCNT_OFFSET ; 
 size_t IEEE80211_MESHPREQ_TCNT_OFFSET_AE ; 
 int IEEE80211_MESHPREQ_TRGT_SZ ; 
 int IEEE80211_MSG_ACTION ; 
 int IEEE80211_MSG_HWMP ; 

__attribute__((used)) static int
verify_mesh_preq_len(struct ieee80211vap *vap,
    const struct ieee80211_frame *wh, const uint8_t *iefrm)
{
	int alloc_sz = -1;
	int ndest = -1;
	if (iefrm[2] & IEEE80211_MESHPREQ_FLAGS_AE) {
		/* Originator External Address  present */
		alloc_sz =  IEEE80211_MESHPREQ_BASE_SZ_AE;
		ndest = iefrm[IEEE80211_MESHPREQ_TCNT_OFFSET_AE];
	} else {
		/* w/o Originator External Address */
		alloc_sz =  IEEE80211_MESHPREQ_BASE_SZ;
		ndest = iefrm[IEEE80211_MESHPREQ_TCNT_OFFSET];
	}
	alloc_sz += ndest * IEEE80211_MESHPREQ_TRGT_SZ;

	if(iefrm[1] != (alloc_sz)) {
		IEEE80211_DISCARD(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_HWMP,
		    wh, NULL, "PREQ (AE=%s) with wrong len",
		    iefrm[2] & IEEE80211_MESHPREQ_FLAGS_AE ? "1" : "0");
		return (-1);
	}
	return ndest;
}