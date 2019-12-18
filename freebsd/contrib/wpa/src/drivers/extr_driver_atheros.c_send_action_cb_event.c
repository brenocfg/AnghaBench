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
struct TYPE_2__ {size_t data_len; int /*<<< orphan*/  ack; int /*<<< orphan*/  const* data; int /*<<< orphan*/  dst; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
union wpa_event_data {TYPE_1__ tx_status; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_send_action_cb {int /*<<< orphan*/  ack; int /*<<< orphan*/  dst_addr; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct atheros_driver_data {int /*<<< orphan*/  hapd; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TX_STATUS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_FC_GET_STYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_FC_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void send_action_cb_event(struct atheros_driver_data *drv,
				 char *data, size_t data_len)
{
	union wpa_event_data event;
	struct ieee80211_send_action_cb *sa;
	const struct ieee80211_hdr *hdr;
	u16 fc;

	if (data_len < sizeof(*sa) + 24) {
		wpa_printf(MSG_DEBUG,
			   "athr: Too short event message (data_len=%d sizeof(*sa)=%d)",
			   (int) data_len, (int) sizeof(*sa));
		wpa_hexdump(MSG_DEBUG, "athr: Short event message",
			    data, data_len);
		return;
	}

	sa = (struct ieee80211_send_action_cb *) data;

	hdr = (const struct ieee80211_hdr *) (sa + 1);
	fc = le_to_host16(hdr->frame_control);

	os_memset(&event, 0, sizeof(event));
	event.tx_status.type = WLAN_FC_GET_TYPE(fc);
	event.tx_status.stype = WLAN_FC_GET_STYPE(fc);
	event.tx_status.dst = sa->dst_addr;
	event.tx_status.data = (const u8 *) hdr;
	event.tx_status.data_len = data_len - sizeof(*sa);
	event.tx_status.ack = sa->ack;
	wpa_supplicant_event(drv->hapd, EVENT_TX_STATUS, &event);
}