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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ RSN_AUTH_KEY_MGMT_802_1X_SHA256 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_802_1X_SUITE_B ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_802_1X_SUITE_B_192 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_DPP ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FILS_SHA256 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FILS_SHA384 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FT_802_1X ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FT_802_1X_SHA384 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FT_FILS_SHA256 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FT_FILS_SHA384 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FT_PSK ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_FT_SAE ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_OSEN ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_OWE ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_PSK_SHA256 ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_SAE ; 
 scalar_t__ RSN_AUTH_KEY_MGMT_UNSPEC_802_1X ; 
 scalar_t__ RSN_SELECTOR_GET (int /*<<< orphan*/  const*) ; 
 int WPA_KEY_MGMT_DPP ; 
 int WPA_KEY_MGMT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_IEEE8021X ; 
 int WPA_KEY_MGMT_FT_IEEE8021X_SHA384 ; 
 int WPA_KEY_MGMT_FT_PSK ; 
 int WPA_KEY_MGMT_FT_SAE ; 
 int WPA_KEY_MGMT_IEEE8021X ; 
 int WPA_KEY_MGMT_IEEE8021X_SHA256 ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 
 int WPA_KEY_MGMT_OSEN ; 
 int WPA_KEY_MGMT_OWE ; 
 int WPA_KEY_MGMT_PSK ; 
 int WPA_KEY_MGMT_PSK_SHA256 ; 
 int WPA_KEY_MGMT_SAE ; 

__attribute__((used)) static int rsn_key_mgmt_to_bitfield(const u8 *s)
{
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_UNSPEC_802_1X)
		return WPA_KEY_MGMT_IEEE8021X;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X)
		return WPA_KEY_MGMT_PSK;
#ifdef CONFIG_IEEE80211R
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FT_802_1X)
		return WPA_KEY_MGMT_FT_IEEE8021X;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FT_PSK)
		return WPA_KEY_MGMT_FT_PSK;
#ifdef CONFIG_SHA384
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FT_802_1X_SHA384)
		return WPA_KEY_MGMT_FT_IEEE8021X_SHA384;
#endif /* CONFIG_SHA384 */
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_IEEE80211W
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_802_1X_SHA256)
		return WPA_KEY_MGMT_IEEE8021X_SHA256;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_PSK_SHA256)
		return WPA_KEY_MGMT_PSK_SHA256;
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_SAE
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_SAE)
		return WPA_KEY_MGMT_SAE;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FT_SAE)
		return WPA_KEY_MGMT_FT_SAE;
#endif /* CONFIG_SAE */
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_802_1X_SUITE_B)
		return WPA_KEY_MGMT_IEEE8021X_SUITE_B;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_802_1X_SUITE_B_192)
		return WPA_KEY_MGMT_IEEE8021X_SUITE_B_192;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FILS_SHA256)
		return WPA_KEY_MGMT_FILS_SHA256;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FILS_SHA384)
		return WPA_KEY_MGMT_FILS_SHA384;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FT_FILS_SHA256)
		return WPA_KEY_MGMT_FT_FILS_SHA256;
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_FT_FILS_SHA384)
		return WPA_KEY_MGMT_FT_FILS_SHA384;
#ifdef CONFIG_OWE
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_OWE)
		return WPA_KEY_MGMT_OWE;
#endif /* CONFIG_OWE */
#ifdef CONFIG_DPP
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_DPP)
		return WPA_KEY_MGMT_DPP;
#endif /* CONFIG_DPP */
	if (RSN_SELECTOR_GET(s) == RSN_AUTH_KEY_MGMT_OSEN)
		return WPA_KEY_MGMT_OSEN;
	return 0;
}