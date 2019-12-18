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
struct wpa_supplicant {scalar_t__ ap_iface; scalar_t__ cross_connect_disallowed; TYPE_1__* current_ssid; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPAS_MODE_INFRA ; 
 scalar_t__ eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_disable_cross_connect (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_enable_cross_connect (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_group_idle_timeout ; 

void wpas_p2p_notif_connected(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->ap_iface || wpa_s->current_ssid == NULL ||
	    wpa_s->current_ssid->mode != WPAS_MODE_INFRA ||
	    wpa_s->cross_connect_disallowed)
		wpas_p2p_disable_cross_connect(wpa_s);
	else
		wpas_p2p_enable_cross_connect(wpa_s);
	if (!wpa_s->ap_iface &&
	    eloop_cancel_timeout(wpas_p2p_group_idle_timeout, wpa_s, NULL) > 0)
		wpa_printf(MSG_DEBUG, "P2P: Cancelled P2P group idle timeout");
}