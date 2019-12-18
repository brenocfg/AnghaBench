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
struct hostapd_data {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPS_EVENT_AP_PIN_DISABLED ; 
 int /*<<< orphan*/  hostapd_wps_ap_pin_disable (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void hostapd_wps_ap_pin_timeout(void *eloop_data, void *user_ctx)
{
	struct hostapd_data *hapd = eloop_data;
	wpa_printf(MSG_DEBUG, "WPS: AP PIN timed out");
	hostapd_wps_ap_pin_disable(hapd);
	wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_AP_PIN_DISABLED);
}