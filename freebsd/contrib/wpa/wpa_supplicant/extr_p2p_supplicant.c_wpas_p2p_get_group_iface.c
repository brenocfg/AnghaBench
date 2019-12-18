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
struct wpa_supplicant {scalar_t__ p2p_first_connection_timeout; int /*<<< orphan*/  ifname; scalar_t__ p2p_go_do_acs; int /*<<< orphan*/  p2p_go_acs_band; struct wpa_supplicant* p2pdev; struct wpa_supplicant* parent; scalar_t__ p2p_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPA_IF_P2P_CLIENT ; 
 int /*<<< orphan*/  WPA_IF_P2P_GO ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_msg_global (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_p2p_add_group_interface (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_p2p_clone_config (struct wpa_supplicant*,struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_create_iface (struct wpa_supplicant*) ; 
 struct wpa_supplicant* wpas_p2p_init_group_interface (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpas_p2p_remove_pending_group_interface (struct wpa_supplicant*) ; 

__attribute__((used)) static struct wpa_supplicant *
wpas_p2p_get_group_iface(struct wpa_supplicant *wpa_s, int addr_allocated,
			 int go)
{
	struct wpa_supplicant *group_wpa_s;

	if (!wpas_p2p_create_iface(wpa_s)) {
		if (wpa_s->p2p_mgmt) {
			/*
			 * We may be called on the p2p_dev interface which
			 * cannot be used for group operations, so always use
			 * the primary interface.
			 */
			wpa_s->parent->p2pdev = wpa_s;
			wpa_s = wpa_s->parent;
		}
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P: Use primary interface for group operations");
		wpa_s->p2p_first_connection_timeout = 0;
		if (wpa_s != wpa_s->p2pdev)
			wpas_p2p_clone_config(wpa_s, wpa_s->p2pdev);
		return wpa_s;
	}

	if (wpas_p2p_add_group_interface(wpa_s, go ? WPA_IF_P2P_GO :
					 WPA_IF_P2P_CLIENT) < 0) {
		wpa_msg_global(wpa_s, MSG_ERROR,
			       "P2P: Failed to add group interface");
		return NULL;
	}
	group_wpa_s = wpas_p2p_init_group_interface(wpa_s, go);
	if (group_wpa_s == NULL) {
		wpa_msg_global(wpa_s, MSG_ERROR,
			       "P2P: Failed to initialize group interface");
		wpas_p2p_remove_pending_group_interface(wpa_s);
		return NULL;
	}

	if (go && wpa_s->p2p_go_do_acs) {
		group_wpa_s->p2p_go_do_acs = wpa_s->p2p_go_do_acs;
		group_wpa_s->p2p_go_acs_band = wpa_s->p2p_go_acs_band;
		wpa_s->p2p_go_do_acs = 0;
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Use separate group interface %s",
		group_wpa_s->ifname);
	group_wpa_s->p2p_first_connection_timeout = 0;
	return group_wpa_s;
}