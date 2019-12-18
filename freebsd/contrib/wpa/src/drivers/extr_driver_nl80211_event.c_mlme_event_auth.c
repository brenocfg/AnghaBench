#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t ies_len; int /*<<< orphan*/  ies; void* status_code; void* auth_transaction; void* auth_type; int /*<<< orphan*/  peer; } ;
union wpa_event_data {TYPE_4__ auth; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int flags; } ;
struct wpa_driver_nl80211_data {int /*<<< orphan*/  ctx; union wpa_event_data* auth_attempt_bssid; int /*<<< orphan*/  auth_bssid; scalar_t__ force_connect_cmd; TYPE_1__ capa; } ;
struct TYPE_6__ {int /*<<< orphan*/  variable; int /*<<< orphan*/  status_code; int /*<<< orphan*/  auth_transaction; int /*<<< orphan*/  auth_alg; } ;
struct TYPE_7__ {TYPE_2__ auth; } ;
struct ieee80211_mgmt {TYPE_3__ u; int /*<<< orphan*/  sa; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  EVENT_AUTH ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_DRIVER_FLAGS_SME ; 
 void* le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void mlme_event_auth(struct wpa_driver_nl80211_data *drv,
			    const u8 *frame, size_t len)
{
	const struct ieee80211_mgmt *mgmt;
	union wpa_event_data event;

	if (!(drv->capa.flags & WPA_DRIVER_FLAGS_SME) &&
	    drv->force_connect_cmd) {
		/*
		 * Avoid reporting two association events that would confuse
		 * the core code.
		 */
		wpa_printf(MSG_DEBUG,
			   "nl80211: Ignore auth event when using driver SME");
		return;
	}

	wpa_printf(MSG_DEBUG, "nl80211: Authenticate event");
	mgmt = (const struct ieee80211_mgmt *) frame;
	if (len < 24 + sizeof(mgmt->u.auth)) {
		wpa_printf(MSG_DEBUG, "nl80211: Too short association event "
			   "frame");
		return;
	}

	os_memcpy(drv->auth_bssid, mgmt->sa, ETH_ALEN);
	os_memset(drv->auth_attempt_bssid, 0, ETH_ALEN);
	os_memset(&event, 0, sizeof(event));
	os_memcpy(event.auth.peer, mgmt->sa, ETH_ALEN);
	event.auth.auth_type = le_to_host16(mgmt->u.auth.auth_alg);
	event.auth.auth_transaction =
		le_to_host16(mgmt->u.auth.auth_transaction);
	event.auth.status_code = le_to_host16(mgmt->u.auth.status_code);
	if (len > 24 + sizeof(mgmt->u.auth)) {
		event.auth.ies = mgmt->u.auth.variable;
		event.auth.ies_len = len - 24 - sizeof(mgmt->u.auth);
	}

	wpa_supplicant_event(drv->ctx, EVENT_AUTH, &event);
}