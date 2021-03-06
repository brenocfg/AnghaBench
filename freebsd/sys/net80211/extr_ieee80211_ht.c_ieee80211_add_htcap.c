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
struct ieee80211_node {int dummy; } ;
struct ieee80211_ie_htcap {int dummy; } ;

/* Variables and functions */
 int IEEE80211_ELEMID_HTCAP ; 
 int* ieee80211_add_htcap_body (int*,struct ieee80211_node*) ; 

uint8_t *
ieee80211_add_htcap(uint8_t *frm, struct ieee80211_node *ni)
{
	frm[0] = IEEE80211_ELEMID_HTCAP;
	frm[1] = sizeof(struct ieee80211_ie_htcap) - 2;
	return ieee80211_add_htcap_body(frm + 2, ni);
}