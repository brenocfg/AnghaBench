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
struct TYPE_8__ {void* reason_code; int /*<<< orphan*/  da; int /*<<< orphan*/  sa; } ;
struct TYPE_7__ {void* reason_code; int /*<<< orphan*/  da; int /*<<< orphan*/  sa; } ;
union wpa_event_data {TYPE_4__ unprot_deauth; TYPE_3__ unprot_disassoc; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct wpa_driver_nl80211_data {int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  reason_code; } ;
struct TYPE_6__ {TYPE_1__ deauth; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  da; int /*<<< orphan*/  sa; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum wpa_event_type { ____Placeholder_wpa_event_type } wpa_event_type ;

/* Variables and functions */
 int EVENT_UNPROT_DEAUTH ; 
 int EVENT_UNPROT_DISASSOC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int,union wpa_event_data*) ; 

__attribute__((used)) static void mlme_event_unprot_disconnect(struct wpa_driver_nl80211_data *drv,
					 enum wpa_event_type type,
					 const u8 *frame, size_t len)
{
	const struct ieee80211_mgmt *mgmt;
	union wpa_event_data event;
	u16 reason_code = 0;

	if (type == EVENT_UNPROT_DEAUTH)
		wpa_printf(MSG_DEBUG, "nl80211: Unprot Deauthenticate event");
	else
		wpa_printf(MSG_DEBUG, "nl80211: Unprot Disassociate event");

	if (len < 24)
		return;

	mgmt = (const struct ieee80211_mgmt *) frame;

	os_memset(&event, 0, sizeof(event));
	/* Note: Same offset for Reason Code in both frame subtypes */
	if (len >= 24 + sizeof(mgmt->u.deauth))
		reason_code = le_to_host16(mgmt->u.deauth.reason_code);

	if (type == EVENT_UNPROT_DISASSOC) {
		event.unprot_disassoc.sa = mgmt->sa;
		event.unprot_disassoc.da = mgmt->da;
		event.unprot_disassoc.reason_code = reason_code;
	} else {
		event.unprot_deauth.sa = mgmt->sa;
		event.unprot_deauth.da = mgmt->da;
		event.unprot_deauth.reason_code = reason_code;
	}

	wpa_supplicant_event(drv->ctx, type, &event);
}