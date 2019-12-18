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
struct wpa_supplicant {int /*<<< orphan*/ * pending_action_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void offchannel_clear_pending_action_tx(struct wpa_supplicant *wpa_s)
{
	wpa_printf(MSG_DEBUG,
		   "Off-channel: Clear pending Action frame TX (pending_action_tx=%p",
		   wpa_s->pending_action_tx);
	wpabuf_free(wpa_s->pending_action_tx);
	wpa_s->pending_action_tx = NULL;
}