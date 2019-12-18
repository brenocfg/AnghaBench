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
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
 int HOSTAPD_MODE_IEEE80211B ; 
 int HOSTAPD_MODE_IEEE80211G ; 

__attribute__((used)) static int is_24ghz_mode(enum hostapd_hw_mode mode)
{
	return mode == HOSTAPD_MODE_IEEE80211B ||
		mode == HOSTAPD_MODE_IEEE80211G;
}