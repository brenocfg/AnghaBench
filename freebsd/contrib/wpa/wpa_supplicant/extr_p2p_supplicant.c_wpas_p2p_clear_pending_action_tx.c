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
struct wpa_supplicant {scalar_t__ p2p_send_action_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offchannel_clear_pending_action_tx (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  offchannel_pending_action_tx (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  offchannel_send_action_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_free_send_action_work (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_send_action_work_timeout ; 

__attribute__((used)) static void wpas_p2p_clear_pending_action_tx(struct wpa_supplicant *wpa_s)
{
	if (!offchannel_pending_action_tx(wpa_s))
		return;

	if (wpa_s->p2p_send_action_work) {
		wpas_p2p_free_send_action_work(wpa_s);
		eloop_cancel_timeout(wpas_p2p_send_action_work_timeout,
				     wpa_s, NULL);
		offchannel_send_action_done(wpa_s);
	}

	wpa_printf(MSG_DEBUG, "P2P: Drop pending Action TX due to new "
		   "operation request");
	offchannel_clear_pending_action_tx(wpa_s);
}