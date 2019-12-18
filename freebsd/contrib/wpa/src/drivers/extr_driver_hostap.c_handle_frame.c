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
struct TYPE_2__ {size_t frame_len; int /*<<< orphan*/ * frame; } ;
union wpa_event_data {TYPE_1__ rx_mgmt; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct hostap_driver_data {int /*<<< orphan*/  hapd; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RX_MGMT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ WLAN_FC_GET_STYPE (scalar_t__) ; 
 scalar_t__ WLAN_FC_GET_TYPE (scalar_t__) ; 
 scalar_t__ WLAN_FC_PVER ; 
 scalar_t__ WLAN_FC_STYPE_BEACON ; 
#define  WLAN_FC_TYPE_CTRL 130 
#define  WLAN_FC_TYPE_DATA 129 
#define  WLAN_FC_TYPE_MGMT 128 
 int /*<<< orphan*/  handle_data (struct hostap_driver_data*,int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 int /*<<< orphan*/  handle_tx_callback (struct hostap_driver_data*,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void handle_frame(struct hostap_driver_data *drv, u8 *buf, size_t len)
{
	struct ieee80211_hdr *hdr;
	u16 fc, type, stype;
	size_t data_len = len;
	int ver;
	union wpa_event_data event;

	/* PSPOLL is only 16 bytes, but driver does not (at least yet) pass
	 * these to user space */
	if (len < 24) {
		wpa_printf(MSG_MSGDUMP, "handle_frame: too short (%lu)",
			   (unsigned long) len);
		return;
	}

	hdr = (struct ieee80211_hdr *) buf;
	fc = le_to_host16(hdr->frame_control);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

	if (type != WLAN_FC_TYPE_MGMT || stype != WLAN_FC_STYPE_BEACON) {
		wpa_hexdump(MSG_MSGDUMP, "Received management frame",
			    buf, len);
	}

	ver = fc & WLAN_FC_PVER;

	/* protocol version 2 is reserved for indicating ACKed frame (TX
	 * callbacks), and version 1 for indicating failed frame (no ACK, TX
	 * callbacks) */
	if (ver == 1 || ver == 2) {
		handle_tx_callback(drv, buf, data_len, ver == 2 ? 1 : 0);
		return;
	} else if (ver != 0) {
		printf("unknown protocol version %d\n", ver);
		return;
	}

	switch (type) {
	case WLAN_FC_TYPE_MGMT:
		os_memset(&event, 0, sizeof(event));
		event.rx_mgmt.frame = buf;
		event.rx_mgmt.frame_len = data_len;
		wpa_supplicant_event(drv->hapd, EVENT_RX_MGMT, &event);
		break;
	case WLAN_FC_TYPE_CTRL:
		wpa_printf(MSG_DEBUG, "CTRL");
		break;
	case WLAN_FC_TYPE_DATA:
		wpa_printf(MSG_DEBUG, "DATA");
		handle_data(drv, buf, data_len, stype);
		break;
	default:
		wpa_printf(MSG_DEBUG, "unknown frame type %d", type);
		break;
	}
}