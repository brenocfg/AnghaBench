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
typedef  scalar_t__ uint32_t ;
struct ieee80211_node {scalar_t__ ni_avgrssi; } ;
typedef  int int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ IEEE80211_RSSI_DUMMY_MARKER ; 
 int IEEE80211_RSSI_GET (scalar_t__) ; 

__attribute__((used)) static int8_t
node_getrssi(const struct ieee80211_node *ni)
{
	uint32_t avgrssi = ni->ni_avgrssi;
	int32_t rssi;

	if (avgrssi == IEEE80211_RSSI_DUMMY_MARKER)
		return 0;
	rssi = IEEE80211_RSSI_GET(avgrssi);
	return rssi < 0 ? 0 : rssi > 127 ? 127 : rssi;
}