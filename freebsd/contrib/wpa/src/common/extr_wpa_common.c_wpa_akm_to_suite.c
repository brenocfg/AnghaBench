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

/* Variables and functions */
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_802_1X_SHA256 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_802_1X_SUITE_B ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_802_1X_SUITE_B_192 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_CCKM ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_DPP ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FILS_SHA256 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FILS_SHA384 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FT_802_1X ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FT_802_1X_SHA384 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FT_FILS_SHA256 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FT_FILS_SHA384 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FT_PSK ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_FT_SAE ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_OSEN ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_OWE ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_PSK_SHA256 ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_SAE ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_UNSPEC_802_1X ; 
 int WPA_KEY_MGMT_CCKM ; 
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

u32 wpa_akm_to_suite(int akm)
{
	if (akm & WPA_KEY_MGMT_FT_IEEE8021X_SHA384)
		return RSN_AUTH_KEY_MGMT_FT_802_1X_SHA384;
	if (akm & WPA_KEY_MGMT_FT_IEEE8021X)
		return RSN_AUTH_KEY_MGMT_FT_802_1X;
	if (akm & WPA_KEY_MGMT_FT_PSK)
		return RSN_AUTH_KEY_MGMT_FT_PSK;
	if (akm & WPA_KEY_MGMT_IEEE8021X_SHA256)
		return RSN_AUTH_KEY_MGMT_802_1X_SHA256;
	if (akm & WPA_KEY_MGMT_IEEE8021X)
		return RSN_AUTH_KEY_MGMT_UNSPEC_802_1X;
	if (akm & WPA_KEY_MGMT_PSK_SHA256)
		return RSN_AUTH_KEY_MGMT_PSK_SHA256;
	if (akm & WPA_KEY_MGMT_PSK)
		return RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X;
	if (akm & WPA_KEY_MGMT_CCKM)
		return RSN_AUTH_KEY_MGMT_CCKM;
	if (akm & WPA_KEY_MGMT_OSEN)
		return RSN_AUTH_KEY_MGMT_OSEN;
	if (akm & WPA_KEY_MGMT_IEEE8021X_SUITE_B)
		return RSN_AUTH_KEY_MGMT_802_1X_SUITE_B;
	if (akm & WPA_KEY_MGMT_IEEE8021X_SUITE_B_192)
		return RSN_AUTH_KEY_MGMT_802_1X_SUITE_B_192;
	if (akm & WPA_KEY_MGMT_FILS_SHA256)
		return RSN_AUTH_KEY_MGMT_FILS_SHA256;
	if (akm & WPA_KEY_MGMT_FILS_SHA384)
		return RSN_AUTH_KEY_MGMT_FILS_SHA384;
	if (akm & WPA_KEY_MGMT_FT_FILS_SHA256)
		return RSN_AUTH_KEY_MGMT_FT_FILS_SHA256;
	if (akm & WPA_KEY_MGMT_FT_FILS_SHA384)
		return RSN_AUTH_KEY_MGMT_FT_FILS_SHA384;
	if (akm & WPA_KEY_MGMT_SAE)
		return RSN_AUTH_KEY_MGMT_SAE;
	if (akm & WPA_KEY_MGMT_FT_SAE)
		return RSN_AUTH_KEY_MGMT_FT_SAE;
	if (akm & WPA_KEY_MGMT_OWE)
		return RSN_AUTH_KEY_MGMT_OWE;
	if (akm & WPA_KEY_MGMT_DPP)
		return RSN_AUTH_KEY_MGMT_DPP;
	if (akm & WPA_KEY_MGMT_OSEN)
		return RSN_AUTH_KEY_MGMT_OSEN;
	return 0;
}