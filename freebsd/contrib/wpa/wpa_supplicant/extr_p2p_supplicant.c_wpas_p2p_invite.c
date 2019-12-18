#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int p2p_persistent_go_freq; int p2p_go_ht40; int p2p_go_vht; int p2p_go_he; int p2p_go_max_oper_chwidth; int p2p_go_vht_center_freq2; int num_multichan_concurrent; TYPE_3__* global; TYPE_2__* parent; int /*<<< orphan*/  pending_invite_ssid_id; int /*<<< orphan*/ * own_addr; scalar_t__ p2p_mgmt; int /*<<< orphan*/ * pending_interface_addr; int /*<<< orphan*/  p2p_auth_invite; } ;
struct wpa_ssid {scalar_t__ mode; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  id; int /*<<< orphan*/ * bssid; } ;
typedef  enum p2p_invite_role { ____Placeholder_p2p_invite_role } p2p_invite_role ;
struct TYPE_6__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; int /*<<< orphan*/ * p2p_invite_group; } ;
struct TYPE_5__ {TYPE_1__* conf; int /*<<< orphan*/ * own_addr; } ;
struct TYPE_4__ {scalar_t__ p2p_ignore_shared_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int P2P_INVITE_ROLE_CLIENT ; 
 int P2P_INVITE_ROLE_GO ; 
 int P2P_MAX_PREF_CHANNELS ; 
 scalar_t__ WPAS_MODE_P2P_GO ; 
 int /*<<< orphan*/  WPA_IF_P2P_GO ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int p2p_invite (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  p2p_set_own_pref_freq_list (int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpas_p2p_add_group_interface (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_p2p_create_iface (struct wpa_supplicant*) ; 
 scalar_t__ wpas_p2p_num_unused_channels (struct wpa_supplicant*) ; 
 int wpas_p2p_setup_freqs (struct wpa_supplicant*,int,int*,int*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wpas_p2p_stop_find_oper (struct wpa_supplicant*) ; 

int wpas_p2p_invite(struct wpa_supplicant *wpa_s, const u8 *peer_addr,
		    struct wpa_ssid *ssid, const u8 *go_dev_addr, int freq,
		    int vht_center_freq2, int ht40, int vht, int max_chwidth,
		    int pref_freq, int he)
{
	enum p2p_invite_role role;
	u8 *bssid = NULL;
	int force_freq = 0;
	int res;
	int no_pref_freq_given = pref_freq == 0;
	unsigned int pref_freq_list[P2P_MAX_PREF_CHANNELS], size;

	wpa_s->global->p2p_invite_group = NULL;
	if (peer_addr)
		os_memcpy(wpa_s->p2p_auth_invite, peer_addr, ETH_ALEN);
	else
		os_memset(wpa_s->p2p_auth_invite, 0, ETH_ALEN);

	wpa_s->p2p_persistent_go_freq = freq;
	wpa_s->p2p_go_ht40 = !!ht40;
	wpa_s->p2p_go_vht = !!vht;
	wpa_s->p2p_go_he = !!he;
	wpa_s->p2p_go_max_oper_chwidth = max_chwidth;
	wpa_s->p2p_go_vht_center_freq2 = vht_center_freq2;
	if (ssid->mode == WPAS_MODE_P2P_GO) {
		role = P2P_INVITE_ROLE_GO;
		if (peer_addr == NULL) {
			wpa_printf(MSG_DEBUG, "P2P: Missing peer "
				   "address in invitation command");
			return -1;
		}
		if (wpas_p2p_create_iface(wpa_s)) {
			if (wpas_p2p_add_group_interface(wpa_s,
							 WPA_IF_P2P_GO) < 0) {
				wpa_printf(MSG_ERROR, "P2P: Failed to "
					   "allocate a new interface for the "
					   "group");
				return -1;
			}
			bssid = wpa_s->pending_interface_addr;
		} else if (wpa_s->p2p_mgmt)
			bssid = wpa_s->parent->own_addr;
		else
			bssid = wpa_s->own_addr;
	} else {
		role = P2P_INVITE_ROLE_CLIENT;
		peer_addr = ssid->bssid;
	}
	wpa_s->pending_invite_ssid_id = ssid->id;

	size = P2P_MAX_PREF_CHANNELS;
	res = wpas_p2p_setup_freqs(wpa_s, freq, &force_freq, &pref_freq,
				   role == P2P_INVITE_ROLE_GO,
				   pref_freq_list, &size);
	if (res)
		return res;

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return -1;

	p2p_set_own_pref_freq_list(wpa_s->global->p2p, pref_freq_list, size);

	if (wpa_s->parent->conf->p2p_ignore_shared_freq &&
	    no_pref_freq_given && pref_freq > 0 &&
	    wpa_s->num_multichan_concurrent > 1 &&
	    wpas_p2p_num_unused_channels(wpa_s) > 0) {
		wpa_printf(MSG_DEBUG, "P2P: Ignore own channel preference %d MHz for invitation due to p2p_ignore_shared_freq=1 configuration",
			   pref_freq);
		pref_freq = 0;
	}

	/*
	 * Stop any find/listen operations before invitation and possibly
	 * connection establishment.
	 */
	wpas_p2p_stop_find_oper(wpa_s);

	return p2p_invite(wpa_s->global->p2p, peer_addr, role, bssid,
			  ssid->ssid, ssid->ssid_len, force_freq, go_dev_addr,
			  1, pref_freq, -1);
}