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
struct wpa_supplicant {scalar_t__ p2p_group_interface; struct wpa_supplicant* p2pdev; int /*<<< orphan*/  p2p_in_provisioning; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ P2P_GROUP_INTERFACE_CLIENT ; 
 int /*<<< orphan*/  WPS_EVENT_OVERLAP ; 
 int /*<<< orphan*/  wpa_msg_ctrl (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_group_formation_failed (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

int wpas_p2p_notif_pbc_overlap(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->p2p_group_interface != P2P_GROUP_INTERFACE_CLIENT &&
	    !wpa_s->p2p_in_provisioning)
		return 0; /* not P2P client operation */

	wpa_printf(MSG_DEBUG, "P2P: Terminate connection due to WPS PBC "
		   "session overlap");
	if (wpa_s != wpa_s->p2pdev)
		wpa_msg_ctrl(wpa_s->p2pdev, MSG_INFO, WPS_EVENT_OVERLAP);
	wpas_p2p_group_formation_failed(wpa_s, 0);
	return 1;
}