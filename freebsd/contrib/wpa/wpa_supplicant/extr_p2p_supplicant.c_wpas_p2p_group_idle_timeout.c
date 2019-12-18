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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ p2p_group_idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_GROUP_REMOVAL_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_group_delete (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_p2p_is_client (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_p2p_group_idle_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;

	if (wpa_s->conf->p2p_group_idle == 0 && !wpas_p2p_is_client(wpa_s)) {
		wpa_printf(MSG_DEBUG, "P2P: Ignore group idle timeout - "
			   "disabled");
		return;
	}

	wpa_printf(MSG_DEBUG, "P2P: Group idle timeout reached - terminate "
		   "group");
	wpas_p2p_group_delete(wpa_s, P2P_GROUP_REMOVAL_IDLE_TIMEOUT);
}