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
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211_node {void* ni_htstbc; void* ni_htopmode; void* ni_ht2ndchan; int /*<<< orphan*/  ni_htctlchan; } ;
struct ieee80211_ie_htinfo {int /*<<< orphan*/  hi_byte45; int /*<<< orphan*/  hi_byte2; int /*<<< orphan*/  hi_byte1; int /*<<< orphan*/  hi_ctrlchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HTINFO_2NDCHAN ; 
 int /*<<< orphan*/  IEEE80211_HTINFO_BASIC_STBCMCS ; 
 int /*<<< orphan*/  IEEE80211_HTINFO_OPMODE ; 
 void* SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
htinfo_parse(struct ieee80211_node *ni,
	const struct ieee80211_ie_htinfo *htinfo)
{
	uint16_t w;

	ni->ni_htctlchan = htinfo->hi_ctrlchannel;
	ni->ni_ht2ndchan = SM(htinfo->hi_byte1, IEEE80211_HTINFO_2NDCHAN);
	w = le16dec(&htinfo->hi_byte2);
	ni->ni_htopmode = SM(w, IEEE80211_HTINFO_OPMODE);
	w = le16dec(&htinfo->hi_byte45);
	ni->ni_htstbc = SM(w, IEEE80211_HTINFO_BASIC_STBCMCS);
}