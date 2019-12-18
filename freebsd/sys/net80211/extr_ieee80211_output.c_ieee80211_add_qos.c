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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_node {int ni_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ELEMID_QOS ; 
 int IEEE80211_NODE_QOS ; 

uint8_t *
ieee80211_add_qos(uint8_t *frm, const struct ieee80211_node *ni)
{
	if (ni->ni_flags & IEEE80211_NODE_QOS) {
		*frm++ = IEEE80211_ELEMID_QOS;
		*frm++ = 1;
		*frm++ = 0;
	}

	return (frm);
}