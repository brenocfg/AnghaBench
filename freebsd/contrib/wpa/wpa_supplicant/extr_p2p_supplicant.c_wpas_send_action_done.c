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
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offchannel_send_action_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radio_work_done (TYPE_1__*) ; 
 int /*<<< orphan*/  wpas_p2p_send_action_work_timeout ; 

__attribute__((used)) static void wpas_send_action_done(void *ctx)
{
	struct wpa_supplicant *wpa_s = ctx;

	if (wpa_s->p2p_send_action_work) {
		eloop_cancel_timeout(wpas_p2p_send_action_work_timeout,
				     wpa_s, NULL);
		os_free(wpa_s->p2p_send_action_work->ctx);
		radio_work_done(wpa_s->p2p_send_action_work);
		wpa_s->p2p_send_action_work = NULL;
	}

	offchannel_send_action_done(wpa_s);
}