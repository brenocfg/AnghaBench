#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct wpa_supplicant {TYPE_1__* ifmsh; } ;
struct sta_info {scalar_t__ my_lid; struct sta_info* next; } ;
struct hostapd_data {struct sta_info* sta_list; } ;
struct TYPE_2__ {struct hostapd_data** bss; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static Boolean llid_in_use(struct wpa_supplicant *wpa_s, u16 llid)
{
	struct sta_info *sta;
	struct hostapd_data *hapd = wpa_s->ifmsh->bss[0];

	for (sta = hapd->sta_list; sta; sta = sta->next) {
		if (sta->my_lid == llid)
			return TRUE;
	}

	return FALSE;
}