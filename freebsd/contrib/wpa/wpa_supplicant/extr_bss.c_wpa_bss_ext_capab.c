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
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_EXT_CAPAB ; 
 int ieee802_11_ext_capab (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wpa_bss_get_ie (struct wpa_bss const*,int /*<<< orphan*/ ) ; 

int wpa_bss_ext_capab(const struct wpa_bss *bss, unsigned int capab)
{
	return ieee802_11_ext_capab(wpa_bss_get_ie(bss, WLAN_EID_EXT_CAPAB),
				    capab);
}