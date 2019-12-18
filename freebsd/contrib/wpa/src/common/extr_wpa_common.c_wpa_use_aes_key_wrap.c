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

/* Variables and functions */
 int WPA_KEY_MGMT_DPP ; 
 int WPA_KEY_MGMT_OSEN ; 
 int WPA_KEY_MGMT_OWE ; 
 scalar_t__ wpa_key_mgmt_ft (int) ; 
 scalar_t__ wpa_key_mgmt_sae (int) ; 
 scalar_t__ wpa_key_mgmt_sha256 (int) ; 
 scalar_t__ wpa_key_mgmt_suite_b (int) ; 

int wpa_use_aes_key_wrap(int akmp)
{
	return akmp == WPA_KEY_MGMT_OSEN ||
		akmp == WPA_KEY_MGMT_OWE ||
		akmp == WPA_KEY_MGMT_DPP ||
		wpa_key_mgmt_ft(akmp) ||
		wpa_key_mgmt_sha256(akmp) ||
		wpa_key_mgmt_sae(akmp) ||
		wpa_key_mgmt_suite_b(akmp);
}