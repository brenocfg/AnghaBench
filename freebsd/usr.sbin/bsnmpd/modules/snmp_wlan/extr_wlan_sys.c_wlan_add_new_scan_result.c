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
struct wlan_scan_result {int /*<<< orphan*/  capinfo; int /*<<< orphan*/  bintval; int /*<<< orphan*/  noise; int /*<<< orphan*/  frequency; int /*<<< orphan*/  rssi; int /*<<< orphan*/  opchannel; } ;
struct wlan_iface {int dummy; } ;
struct ieee80211req_scan_result {int /*<<< orphan*/  isr_capinfo; int /*<<< orphan*/  isr_intval; int /*<<< orphan*/  isr_noise; int /*<<< orphan*/  isr_freq; int /*<<< orphan*/  isr_rssi; int /*<<< orphan*/  isr_flags; int /*<<< orphan*/  isr_bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlan_channel_flags_to_snmp_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_peercaps_to_snmp (int /*<<< orphan*/ ) ; 
 scalar_t__ wlan_scan_add_result (struct wlan_iface*,struct wlan_scan_result*) ; 
 int /*<<< orphan*/  wlan_scan_free_result (struct wlan_scan_result*) ; 
 struct wlan_scan_result* wlan_scan_new_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wlan_add_new_scan_result(struct wlan_iface *wif,
    const struct ieee80211req_scan_result *isr, uint8_t *ssid)
{
	struct wlan_scan_result *sr;

	if ((sr = wlan_scan_new_result(ssid, isr->isr_bssid)) == NULL)
		return (-1);

	sr->opchannel = wlan_channel_flags_to_snmp_phy(isr->isr_flags);
	sr->rssi = isr->isr_rssi;
	sr->frequency = isr->isr_freq;
	sr->noise = isr->isr_noise;
	sr->bintval = isr->isr_intval;
	sr->capinfo = wlan_peercaps_to_snmp(isr->isr_capinfo);

	if (wlan_scan_add_result(wif, sr) < 0) {
		wlan_scan_free_result(sr);
		return (-1);
	}

	return (0);
}