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
#define  WPA_KEY_MGMT_DPP 135 
#define  WPA_KEY_MGMT_FILS_SHA256 134 
#define  WPA_KEY_MGMT_FILS_SHA384 133 
#define  WPA_KEY_MGMT_FT_FILS_SHA256 132 
#define  WPA_KEY_MGMT_FT_FILS_SHA384 131 
#define  WPA_KEY_MGMT_FT_IEEE8021X_SHA384 130 
#define  WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 129 
#define  WPA_KEY_MGMT_OWE 128 

__attribute__((used)) static unsigned int wpa_kek_len(int akmp, size_t pmk_len)
{
	switch (akmp) {
	case WPA_KEY_MGMT_FILS_SHA384:
	case WPA_KEY_MGMT_FT_FILS_SHA384:
		return 64;
	case WPA_KEY_MGMT_IEEE8021X_SUITE_B_192:
	case WPA_KEY_MGMT_FILS_SHA256:
	case WPA_KEY_MGMT_FT_FILS_SHA256:
	case WPA_KEY_MGMT_FT_IEEE8021X_SHA384:
		return 32;
	case WPA_KEY_MGMT_DPP:
		return pmk_len <= 32 ? 16 : 32;
	case WPA_KEY_MGMT_OWE:
		return pmk_len <= 32 ? 16 : 32;
	default:
		return 16;
	}
}