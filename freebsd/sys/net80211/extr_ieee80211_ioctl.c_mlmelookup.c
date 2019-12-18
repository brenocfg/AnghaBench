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
struct scanlookup {scalar_t__ esslen; struct ieee80211_scan_entry const* se; int /*<<< orphan*/  essid; int /*<<< orphan*/  mac; } ;
struct ieee80211_scan_entry {scalar_t__* se_ssid; int /*<<< orphan*/  se_macaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void
mlmelookup(void *arg, const struct ieee80211_scan_entry *se)
{
	struct scanlookup *look = arg;

	if (!IEEE80211_ADDR_EQ(look->mac, se->se_macaddr))
		return;
	if (look->esslen != 0) {
		if (se->se_ssid[1] != look->esslen)
			return;
		if (memcmp(look->essid, se->se_ssid+2, look->esslen))
			return;
	}
	look->se = se;
}