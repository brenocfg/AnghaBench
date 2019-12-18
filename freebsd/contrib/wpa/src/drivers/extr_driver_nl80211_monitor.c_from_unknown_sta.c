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
struct TYPE_2__ {int wds; int /*<<< orphan*/  addr; int /*<<< orphan*/  bssid; } ;
union wpa_event_data {TYPE_1__ rx_from_unknown; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wpa_driver_nl80211_data {int /*<<< orphan*/  ctx; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RX_FROM_UNKNOWN ; 
 int WLAN_FC_FROMDS ; 
 int WLAN_FC_TODS ; 
 int /*<<< orphan*/  get_hdr_bssid (struct ieee80211_hdr*,size_t) ; 
 int le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void from_unknown_sta(struct wpa_driver_nl80211_data *drv,
			     u8 *buf, size_t len)
{
	struct ieee80211_hdr *hdr = (void *)buf;
	u16 fc;
	union wpa_event_data event;

	if (len < sizeof(*hdr))
		return;

	fc = le_to_host16(hdr->frame_control);

	os_memset(&event, 0, sizeof(event));
	event.rx_from_unknown.bssid = get_hdr_bssid(hdr, len);
	event.rx_from_unknown.addr = hdr->addr2;
	event.rx_from_unknown.wds = (fc & (WLAN_FC_FROMDS | WLAN_FC_TODS)) ==
		(WLAN_FC_FROMDS | WLAN_FC_TODS);
	wpa_supplicant_event(drv->ctx, EVENT_RX_FROM_UNKNOWN, &event);
}