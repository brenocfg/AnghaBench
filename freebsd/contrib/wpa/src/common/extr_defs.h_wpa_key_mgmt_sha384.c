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
 int WPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_IEEE8021X_SHA384 ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 

__attribute__((used)) static inline int wpa_key_mgmt_sha384(int akm)
{
	return !!(akm & (WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 |
			 WPA_KEY_MGMT_FT_IEEE8021X_SHA384 |
			 WPA_KEY_MGMT_FILS_SHA384 |
			 WPA_KEY_MGMT_FT_FILS_SHA384));
}