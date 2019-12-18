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
struct ieee80211_tx_ampdu {int dummy; } ;
struct ieee80211_node {struct ieee80211_tx_ampdu* ni_tx_ampdu; } ;
struct ath_node {struct ieee80211_node an_node; } ;

/* Variables and functions */
 int IEEE80211_NONQOS_TID ; 

struct ieee80211_tx_ampdu *
ath_tx_get_tx_tid(struct ath_node *an, int tid)
{
	struct ieee80211_node *ni = &an->an_node;
	struct ieee80211_tx_ampdu *tap;

	if (tid == IEEE80211_NONQOS_TID)
		return NULL;

	tap = &ni->ni_tx_ampdu[tid];
	return tap;
}