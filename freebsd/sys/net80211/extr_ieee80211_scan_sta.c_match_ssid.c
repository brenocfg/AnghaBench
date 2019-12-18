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
struct ieee80211_scan_ssid {int /*<<< orphan*/  len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ match_id (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
match_ssid(const uint8_t *ie,
	int nssid, const struct ieee80211_scan_ssid ssids[])
{
	int i;

	for (i = 0; i < nssid; i++) {
		if (match_id(ie, ssids[i].ssid, ssids[i].len))
			return 1;
	}
	return 0;
}