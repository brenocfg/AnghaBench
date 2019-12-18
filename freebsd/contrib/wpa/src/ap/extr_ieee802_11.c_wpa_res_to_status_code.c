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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STATUS_AKMP_NOT_VALID ; 
 int /*<<< orphan*/  WLAN_STATUS_CIPHER_REJECTED_PER_POLICY ; 
 int /*<<< orphan*/  WLAN_STATUS_GROUP_CIPHER_NOT_VALID ; 
 int /*<<< orphan*/  WLAN_STATUS_INVALID_IE ; 
 int /*<<< orphan*/  WLAN_STATUS_INVALID_MDIE ; 
 int /*<<< orphan*/  WLAN_STATUS_INVALID_PMKID ; 
 int /*<<< orphan*/  WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID ; 
 int /*<<< orphan*/  WLAN_STATUS_ROBUST_MGMT_FRAME_POLICY_VIOLATION ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int WPA_ALLOC_FAIL ; 
 int WPA_IE_OK ; 
 int WPA_INVALID_AKMP ; 
 int WPA_INVALID_GROUP ; 
 int WPA_INVALID_MDIE ; 
 int WPA_INVALID_MGMT_GROUP_CIPHER ; 
 int WPA_INVALID_PAIRWISE ; 
 int WPA_INVALID_PMKID ; 
 int WPA_MGMT_FRAME_PROTECTION_VIOLATION ; 

__attribute__((used)) static u16 wpa_res_to_status_code(int res)
{
	if (res == WPA_INVALID_GROUP)
		return WLAN_STATUS_GROUP_CIPHER_NOT_VALID;
	if (res == WPA_INVALID_PAIRWISE)
		return WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID;
	if (res == WPA_INVALID_AKMP)
		return WLAN_STATUS_AKMP_NOT_VALID;
	if (res == WPA_ALLOC_FAIL)
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
#ifdef CONFIG_IEEE80211W
	if (res == WPA_MGMT_FRAME_PROTECTION_VIOLATION)
		return WLAN_STATUS_ROBUST_MGMT_FRAME_POLICY_VIOLATION;
	if (res == WPA_INVALID_MGMT_GROUP_CIPHER)
		return WLAN_STATUS_CIPHER_REJECTED_PER_POLICY;
#endif /* CONFIG_IEEE80211W */
	if (res == WPA_INVALID_MDIE)
		return WLAN_STATUS_INVALID_MDIE;
	if (res == WPA_INVALID_PMKID)
		return WLAN_STATUS_INVALID_PMKID;
	if (res != WPA_IE_OK)
		return WLAN_STATUS_INVALID_IE;
	return WLAN_STATUS_SUCCESS;
}