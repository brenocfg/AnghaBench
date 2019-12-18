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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_driver_ndis_data {int dummy; } ;
typedef  enum event_types { ____Placeholder_event_types } event_types ;

/* Variables and functions */
#define  EVENT_ADAPTER_ARRIVAL 132 
#define  EVENT_ADAPTER_REMOVAL 131 
#define  EVENT_CONNECT 130 
#define  EVENT_DISCONNECT 129 
#define  EVENT_MEDIA_SPECIFIC 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  wpa_driver_ndis_event_adapter_arrival (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_event_adapter_removal (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_event_connect (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_event_disconnect (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_driver_ndis_event_media_specific (struct wpa_driver_ndis_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpa_driver_ndis_event_process(struct wpa_driver_ndis_data *drv,
					  u8 *buf, size_t len)
{
	u8 *pos, *data = NULL;
	enum event_types type;
	size_t data_len = 0;

	wpa_hexdump(MSG_MSGDUMP, "NDIS: received event data", buf, len);
	if (len < sizeof(int))
		return;
	type = *((int *) buf);
	pos = buf + sizeof(int);
	wpa_printf(MSG_DEBUG, "NDIS: event - type %d", type);

	if (buf + len - pos > 2) {
		data_len = (int) *pos++ << 8;
		data_len += *pos++;
		if (data_len > (size_t) (buf + len - pos)) {
			wpa_printf(MSG_DEBUG, "NDIS: event data overflow");
			return;
		}
		data = pos;
		wpa_hexdump(MSG_MSGDUMP, "NDIS: event data", data, data_len);
	}

	switch (type) {
	case EVENT_CONNECT:
		wpa_driver_ndis_event_connect(drv);
		break;
	case EVENT_DISCONNECT:
		wpa_driver_ndis_event_disconnect(drv);
		break;
	case EVENT_MEDIA_SPECIFIC:
		wpa_driver_ndis_event_media_specific(drv, data, data_len);
		break;
	case EVENT_ADAPTER_ARRIVAL:
		wpa_driver_ndis_event_adapter_arrival(drv);
		break;
	case EVENT_ADAPTER_REMOVAL:
		wpa_driver_ndis_event_adapter_removal(drv);
		break;
	}
}