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
struct wpa_supplicant {scalar_t__ wpa_state; struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {int mode; int /*<<< orphan*/  p2p_group; } ;
typedef  enum wpas_p2p_role { ____Placeholder_wpas_p2p_role } wpas_p2p_role ;

/* Variables and functions */
#define  WPAS_MODE_INFRA 130 
#define  WPAS_MODE_P2P_GO 129 
#define  WPAS_MODE_P2P_GROUP_FORMATION 128 
 int WPAS_P2P_ROLE_CLIENT ; 
 int WPAS_P2P_ROLE_DEVICE ; 
 int WPAS_P2P_ROLE_GO ; 
 scalar_t__ WPA_COMPLETED ; 

__attribute__((used)) static enum wpas_p2p_role wpas_get_p2p_role(struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid = wpa_s->current_ssid;

	if (!ssid)
		return WPAS_P2P_ROLE_DEVICE;
	if (wpa_s->wpa_state != WPA_COMPLETED)
		return WPAS_P2P_ROLE_DEVICE;

	switch (ssid->mode) {
	case WPAS_MODE_P2P_GO:
	case WPAS_MODE_P2P_GROUP_FORMATION:
		return WPAS_P2P_ROLE_GO;
	case WPAS_MODE_INFRA:
		if (ssid->p2p_group)
			return WPAS_P2P_ROLE_CLIENT;
		return WPAS_P2P_ROLE_DEVICE;
	default:
		return WPAS_P2P_ROLE_DEVICE;
	}
}