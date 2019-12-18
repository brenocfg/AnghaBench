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
struct TYPE_2__ {size_t data_len; int ack; int /*<<< orphan*/ * data; int /*<<< orphan*/  dst; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
union wpa_event_data {TYPE_1__ tx_status; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
struct hostap_driver_data {int /*<<< orphan*/  hapd; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TX_STATUS ; 
 int /*<<< orphan*/  WLAN_FC_GET_STYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_FC_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void handle_tx_callback(struct hostap_driver_data *drv, u8 *buf,
			       size_t len, int ok)
{
	struct ieee80211_hdr *hdr;
	u16 fc;
	union wpa_event_data event;

	hdr = (struct ieee80211_hdr *) buf;
	fc = le_to_host16(hdr->frame_control);

	os_memset(&event, 0, sizeof(event));
	event.tx_status.type = WLAN_FC_GET_TYPE(fc);
	event.tx_status.stype = WLAN_FC_GET_STYPE(fc);
	event.tx_status.dst = hdr->addr1;
	event.tx_status.data = buf;
	event.tx_status.data_len = len;
	event.tx_status.ack = ok;
	wpa_supplicant_event(drv->hapd, EVENT_TX_STATUS, &event);
}