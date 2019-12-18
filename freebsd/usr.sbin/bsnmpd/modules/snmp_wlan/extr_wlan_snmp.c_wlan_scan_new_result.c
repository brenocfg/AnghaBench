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
typedef  char uint8_t ;
struct wlan_scan_result {int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 scalar_t__ IEEE80211_NWID_LEN ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wlan_scan_result*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

struct wlan_scan_result *
wlan_scan_new_result(const uint8_t *ssid, const uint8_t *bssid)
{
	struct wlan_scan_result *sr;

	sr = (struct wlan_scan_result *)malloc(sizeof(*sr));
	if (sr == NULL)
		return (NULL);

	memset(sr, 0, sizeof(*sr));
	if (ssid[0] != '\0')
		strlcpy(sr->ssid, ssid, IEEE80211_NWID_LEN + 1);
	memcpy(sr->bssid, bssid, IEEE80211_ADDR_LEN);

	return (sr);
}