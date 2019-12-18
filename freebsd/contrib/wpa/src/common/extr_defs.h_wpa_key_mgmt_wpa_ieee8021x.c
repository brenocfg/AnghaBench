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
 int WPA_KEY_MGMT_CCKM ; 
 int WPA_KEY_MGMT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_IEEE8021X ; 
 int WPA_KEY_MGMT_FT_IEEE8021X_SHA384 ; 
 int WPA_KEY_MGMT_IEEE8021X ; 
 int WPA_KEY_MGMT_IEEE8021X_SHA256 ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 
 int WPA_KEY_MGMT_OSEN ; 

__attribute__((used)) static inline int wpa_key_mgmt_wpa_ieee8021x(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_IEEE8021X |
			 WPA_KEY_MGMT_FT_IEEE8021X |
			 WPA_KEY_MGMT_FT_IEEE8021X_SHA384 |
			 WPA_KEY_MGMT_CCKM |
			 WPA_KEY_MGMT_OSEN |
			 WPA_KEY_MGMT_IEEE8021X_SHA256 |
			 WPA_KEY_MGMT_IEEE8021X_SUITE_B |
			 WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 |
			 WPA_KEY_MGMT_FILS_SHA256 |
			 WPA_KEY_MGMT_FILS_SHA384 |
			 WPA_KEY_MGMT_FT_FILS_SHA256 |
			 WPA_KEY_MGMT_FT_FILS_SHA384));
}