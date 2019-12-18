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
struct wpa_supplicant {TYPE_1__* p2p_send_action_work; } ;
struct send_action_work {int wait_time; } ;
struct TYPE_2__ {struct send_action_work* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wpas_p2p_free_send_action_work (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_send_action_work_timeout ; 

__attribute__((used)) static void wpas_p2p_action_tx_clear(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->p2p_send_action_work) {
		struct send_action_work *awork;

		awork = wpa_s->p2p_send_action_work->ctx;
		wpa_printf(MSG_DEBUG,
			   "P2P: Clear Action TX work @%p (wait_time=%u)",
			   wpa_s->p2p_send_action_work, awork->wait_time);
		if (awork->wait_time == 0) {
			wpas_p2p_free_send_action_work(wpa_s);
		} else {
			/*
			 * In theory, this should not be needed, but number of
			 * places in the P2P code is still using non-zero wait
			 * time for the last Action frame in the sequence and
			 * some of these do not call send_action_done().
			 */
			eloop_cancel_timeout(wpas_p2p_send_action_work_timeout,
					     wpa_s, NULL);
			eloop_register_timeout(
				0, awork->wait_time * 1000,
				wpas_p2p_send_action_work_timeout,
				wpa_s, NULL);
		}
	}
}