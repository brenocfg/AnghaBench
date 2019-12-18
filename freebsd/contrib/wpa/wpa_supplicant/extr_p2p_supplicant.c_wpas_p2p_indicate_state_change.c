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
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPAS_P2P_CHANNEL_UPDATE_STATE_CHANGE ; 
 int /*<<< orphan*/  wpas_p2p_update_channel_list (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

void wpas_p2p_indicate_state_change(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return;

	wpas_p2p_update_channel_list(wpa_s,
				     WPAS_P2P_CHANNEL_UPDATE_STATE_CHANGE);
}