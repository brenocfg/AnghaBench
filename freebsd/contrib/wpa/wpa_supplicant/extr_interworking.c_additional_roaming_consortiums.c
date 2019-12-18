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
typedef  scalar_t__ u8 ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_ROAMING_CONSORTIUM ; 
 scalar_t__* wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int additional_roaming_consortiums(struct wpa_bss *bss)
{
	const u8 *ie;
	ie = wpa_bss_get_ie(bss, WLAN_EID_ROAMING_CONSORTIUM);
	if (ie == NULL || ie[1] == 0)
		return 0;
	return ie[2]; /* Number of ANQP OIs */
}