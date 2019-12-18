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
struct hostapd_hw_modes {int flags; int* vht_mcs_set; } ;

/* Variables and functions */
 int HOSTAPD_MODE_FLAG_VHT_INFO_KNOWN ; 

int vht_supported(const struct hostapd_hw_modes *mode)
{
	if (!(mode->flags & HOSTAPD_MODE_FLAG_VHT_INFO_KNOWN)) {
		/*
		 * The driver did not indicate whether it supports VHT. Assume
		 * it does to avoid connection issues.
		 */
		return 1;
	}

	/*
	 * A VHT non-AP STA shall support MCS 0-7 for one spatial stream.
	 * TODO: Verify if this complies with the standard
	 */
	return (mode->vht_mcs_set[0] & 0x3) != 3;
}