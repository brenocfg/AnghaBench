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
struct wpa_supplicant {int /*<<< orphan*/  eapol; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_sm_notify_ctrl_response (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_ctrl_eapol_response(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	eapol_sm_notify_ctrl_response(wpa_s->eapol);
}