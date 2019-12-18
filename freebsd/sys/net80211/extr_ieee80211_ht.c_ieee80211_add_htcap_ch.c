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
struct ieee80211_ie_htcap {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int IEEE80211_ELEMID_HTCAP ; 
 int* ieee80211_add_htcap_body_ch (int*,struct ieee80211vap*,struct ieee80211_channel*) ; 

uint8_t *
ieee80211_add_htcap_ch(uint8_t *frm, struct ieee80211vap *vap,
    struct ieee80211_channel *c)
{
	frm[0] = IEEE80211_ELEMID_HTCAP;
	frm[1] = sizeof(struct ieee80211_ie_htcap) - 2;
	return ieee80211_add_htcap_body_ch(frm + 2, vap, c);
}