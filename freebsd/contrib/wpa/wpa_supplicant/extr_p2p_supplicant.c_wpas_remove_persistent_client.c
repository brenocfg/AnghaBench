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
struct wpa_supplicant {int /*<<< orphan*/  p2pdev; struct wpa_ssid* current_ssid; TYPE_1__* global; } ;
struct wpa_ssid {scalar_t__ mode; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  p2p_persistent_group; } ;
struct TYPE_2__ {struct wpa_supplicant* p2p_invite_group; } ;

/* Variables and functions */
 scalar_t__ WPAS_MODE_P2P_GO ; 
 struct wpa_ssid* wpas_p2p_get_persistent (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_remove_persistent_peer (struct wpa_supplicant*,struct wpa_ssid*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void wpas_remove_persistent_client(struct wpa_supplicant *wpa_s,
					  const u8 *peer)
{
	struct wpa_ssid *ssid;

	wpa_s = wpa_s->global->p2p_invite_group;
	if (wpa_s == NULL)
		return; /* No known invitation group */
	ssid = wpa_s->current_ssid;
	if (ssid == NULL || ssid->mode != WPAS_MODE_P2P_GO ||
	    !ssid->p2p_persistent_group)
		return; /* Not operating as a GO in persistent group */
	ssid = wpas_p2p_get_persistent(wpa_s->p2pdev, peer,
				       ssid->ssid, ssid->ssid_len);
	wpas_remove_persistent_peer(wpa_s, ssid, peer, 1);
}