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
struct wpa_supplicant {TYPE_1__* ifmsh; } ;
struct sta_info {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct TYPE_2__ {struct hostapd_data** bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_free_sta (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,struct sta_info*) ; 
 int /*<<< orphan*/  plink_timer ; 

__attribute__((used)) static void mesh_mpm_fsm_restart(struct wpa_supplicant *wpa_s,
				 struct sta_info *sta)
{
	struct hostapd_data *hapd = wpa_s->ifmsh->bss[0];

	eloop_cancel_timeout(plink_timer, wpa_s, sta);

	ap_free_sta(hapd, sta);
}