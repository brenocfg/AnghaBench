#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* ifmsh; struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {int /*<<< orphan*/  no_auto_peer; } ;
struct sta_info {scalar_t__ plink_state; TYPE_2__* sae; } ;
struct mesh_conf {scalar_t__ security; } ;
struct hostapd_data {int /*<<< orphan*/  mesh_required_peer; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {struct mesh_conf* mconf; struct hostapd_data** bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ MESH_CONF_SEC_NONE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ PLINK_ESTAB ; 
 scalar_t__ PLINK_OPN_SNT ; 
 scalar_t__ SAE_NOTHING ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_mpm_plink_open (struct wpa_supplicant*,struct sta_info*,scalar_t__) ; 
 int /*<<< orphan*/  mesh_rsn_auth_sae_sta (struct wpa_supplicant*,struct sta_info*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_add_timer ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 

int mesh_mpm_connect_peer(struct wpa_supplicant *wpa_s, const u8 *addr,
			  int duration)
{
	struct wpa_ssid *ssid = wpa_s->current_ssid;
	struct hostapd_data *hapd;
	struct sta_info *sta;
	struct mesh_conf *conf;

	if (!wpa_s->ifmsh) {
		wpa_msg(wpa_s, MSG_INFO, "Mesh is not prepared yet");
		return -1;
	}

	if (!ssid || !ssid->no_auto_peer) {
		wpa_msg(wpa_s, MSG_INFO,
			"This command is available only with no_auto_peer mesh network");
		return -1;
	}

	hapd = wpa_s->ifmsh->bss[0];
	conf = wpa_s->ifmsh->mconf;

	sta = ap_get_sta(hapd, addr);
	if (!sta) {
		wpa_msg(wpa_s, MSG_INFO, "No such mesh peer");
		return -1;
	}

	if ((PLINK_OPN_SNT <= sta->plink_state &&
	    sta->plink_state <= PLINK_ESTAB) ||
	    (sta->sae && sta->sae->state > SAE_NOTHING)) {
		wpa_msg(wpa_s, MSG_INFO,
			"Specified peer is connecting/connected");
		return -1;
	}

	if (conf->security == MESH_CONF_SEC_NONE) {
		mesh_mpm_plink_open(wpa_s, sta, PLINK_OPN_SNT);
	} else {
		mesh_rsn_auth_sae_sta(wpa_s, sta);
		os_memcpy(hapd->mesh_required_peer, addr, ETH_ALEN);
		eloop_register_timeout(duration == -1 ? 10 : duration, 0,
				       peer_add_timer, wpa_s, NULL);
	}

	return 0;
}