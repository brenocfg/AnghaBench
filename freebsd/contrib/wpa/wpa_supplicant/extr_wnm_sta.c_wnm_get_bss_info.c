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
typedef  int /*<<< orphan*/  u32 ;
struct wpa_supplicant {int /*<<< orphan*/  current_bss; } ;
struct wpa_bss {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_APSD ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_AP_UNKNOWN_REACH ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_DELAYED_BA ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_HT ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_IMM_BA ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_MOBILITY_DOMAIN ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_QOS ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_RM ; 
 int /*<<< orphan*/  NEI_REP_BSSID_INFO_SPECTRUM_MGMT ; 
 int WLAN_CAPABILITY_APSD ; 
 int WLAN_CAPABILITY_DELAYED_BLOCK_ACK ; 
 int WLAN_CAPABILITY_IMM_BLOCK_ACK ; 
 int WLAN_CAPABILITY_QOS ; 
 int WLAN_CAPABILITY_RADIO_MEASUREMENT ; 
 int WLAN_CAPABILITY_SPECTRUM_MGMT ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAP ; 
 int /*<<< orphan*/  WLAN_EID_MOBILITY_DOMAIN ; 
 scalar_t__ wpa_bss_ies_eq (struct wpa_bss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 wnm_get_bss_info(struct wpa_supplicant *wpa_s, struct wpa_bss *bss)
{
	u32 info = 0;

	info |= NEI_REP_BSSID_INFO_AP_UNKNOWN_REACH;

	/*
	 * Leave the security and key scope bits unset to indicate that the
	 * security information is not available.
	 */

	if (bss->caps & WLAN_CAPABILITY_SPECTRUM_MGMT)
		info |= NEI_REP_BSSID_INFO_SPECTRUM_MGMT;
	if (bss->caps & WLAN_CAPABILITY_QOS)
		info |= NEI_REP_BSSID_INFO_QOS;
	if (bss->caps & WLAN_CAPABILITY_APSD)
		info |= NEI_REP_BSSID_INFO_APSD;
	if (bss->caps & WLAN_CAPABILITY_RADIO_MEASUREMENT)
		info |= NEI_REP_BSSID_INFO_RM;
	if (bss->caps & WLAN_CAPABILITY_DELAYED_BLOCK_ACK)
		info |= NEI_REP_BSSID_INFO_DELAYED_BA;
	if (bss->caps & WLAN_CAPABILITY_IMM_BLOCK_ACK)
		info |= NEI_REP_BSSID_INFO_IMM_BA;
	if (wpa_bss_ies_eq(bss, wpa_s->current_bss, WLAN_EID_MOBILITY_DOMAIN))
		info |= NEI_REP_BSSID_INFO_MOBILITY_DOMAIN;
	if (wpa_bss_ies_eq(bss, wpa_s->current_bss, WLAN_EID_HT_CAP))
		info |= NEI_REP_BSSID_INFO_HT;

	return info;
}