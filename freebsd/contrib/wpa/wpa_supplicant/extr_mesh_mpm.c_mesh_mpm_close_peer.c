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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* ifmsh; } ;
struct sta_info {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct TYPE_2__ {struct hostapd_data** bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mesh_mpm_plink_close (struct hostapd_data*,struct sta_info*,struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 

int mesh_mpm_close_peer(struct wpa_supplicant *wpa_s, const u8 *addr)
{
	struct hostapd_data *hapd;
	struct sta_info *sta;

	if (!wpa_s->ifmsh) {
		wpa_msg(wpa_s, MSG_INFO, "Mesh is not prepared yet");
		return -1;
	}

	hapd = wpa_s->ifmsh->bss[0];
	sta = ap_get_sta(hapd, addr);
	if (!sta) {
		wpa_msg(wpa_s, MSG_INFO, "No such mesh peer");
		return -1;
	}

	return mesh_mpm_plink_close(hapd, sta, wpa_s) == 0 ? 0 : -1;
}