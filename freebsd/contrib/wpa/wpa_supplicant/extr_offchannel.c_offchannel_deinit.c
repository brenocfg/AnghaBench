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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offchannel_clear_pending_action_tx (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_send_action_cb ; 

void offchannel_deinit(struct wpa_supplicant *wpa_s)
{
	offchannel_clear_pending_action_tx(wpa_s);
	eloop_cancel_timeout(wpas_send_action_cb, wpa_s, NULL);
}