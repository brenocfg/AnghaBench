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
struct wps_event_pwd_auth_fail {int /*<<< orphan*/  peer_macaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  failure_reason; int /*<<< orphan*/  status; } ;
struct hostapd_data {TYPE_1__ wps_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_EI_AUTH_FAILURE ; 
 int /*<<< orphan*/  WPS_STATUS_FAILURE ; 
 int /*<<< orphan*/  hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,struct wps_event_pwd_auth_fail*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_pwd_auth_fail ; 

__attribute__((used)) static void hostapd_pwd_auth_fail(struct hostapd_data *hapd,
				  struct wps_event_pwd_auth_fail *data)
{
	/* Update WPS Status - Authentication Failure */
	wpa_printf(MSG_DEBUG, "WPS: Authentication failure update");
	hapd->wps_stats.status = WPS_STATUS_FAILURE;
	hapd->wps_stats.failure_reason = WPS_EI_AUTH_FAILURE;
	os_memcpy(hapd->wps_stats.peer_addr, data->peer_macaddr, ETH_ALEN);

	hostapd_wps_for_each(hapd, wps_pwd_auth_fail, data);
}