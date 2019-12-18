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
struct hostapd_hw_modes {int flags; int* mcs_set; } ;

/* Variables and functions */
 int HOSTAPD_MODE_FLAG_HT_INFO_KNOWN ; 

int ht_supported(const struct hostapd_hw_modes *mode)
{
	if (!(mode->flags & HOSTAPD_MODE_FLAG_HT_INFO_KNOWN)) {
		/*
		 * The driver did not indicate whether it supports HT. Assume
		 * it does to avoid connection issues.
		 */
		return 1;
	}

	/*
	 * IEEE Std 802.11n-2009 20.1.1:
	 * An HT non-AP STA shall support all EQM rates for one spatial stream.
	 */
	return mode->mcs_set[0] == 0xff;
}