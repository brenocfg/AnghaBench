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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  initiator; } ;
union wpa_event_data {TYPE_1__ channel_list_changed; } ;
struct wpa_supplicant {int /*<<< orphan*/  setband; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CHANNEL_LIST_CHANGED ; 
 int /*<<< orphan*/  REGDOM_SET_BY_USER ; 
 int /*<<< orphan*/  REGDOM_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  WPA_SETBAND_2G ; 
 int /*<<< orphan*/  WPA_SETBAND_5G ; 
 int /*<<< orphan*/  WPA_SETBAND_AUTO ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ wpa_drv_setband (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_event (struct wpa_supplicant*,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static int wpas_ctrl_set_band(struct wpa_supplicant *wpa_s, char *band)
{
	union wpa_event_data event;

	if (os_strcmp(band, "AUTO") == 0)
		wpa_s->setband = WPA_SETBAND_AUTO;
	else if (os_strcmp(band, "5G") == 0)
		wpa_s->setband = WPA_SETBAND_5G;
	else if (os_strcmp(band, "2G") == 0)
		wpa_s->setband = WPA_SETBAND_2G;
	else
		return -1;

	if (wpa_drv_setband(wpa_s, wpa_s->setband) == 0) {
		os_memset(&event, 0, sizeof(event));
		event.channel_list_changed.initiator = REGDOM_SET_BY_USER;
		event.channel_list_changed.type = REGDOM_TYPE_UNKNOWN;
		wpa_supplicant_event(wpa_s, EVENT_CHANNEL_LIST_CHANGED, &event);
	}

	return 0;
}