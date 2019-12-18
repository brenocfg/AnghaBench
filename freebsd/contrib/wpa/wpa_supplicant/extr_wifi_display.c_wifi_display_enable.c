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
struct wpa_global {int wifi_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wifi_display_update_wfd_ie (struct wpa_global*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

void wifi_display_enable(struct wpa_global *global, int enabled)
{
	wpa_printf(MSG_DEBUG, "WFD: Wi-Fi Display %s",
		   enabled ? "enabled" : "disabled");
	global->wifi_display = enabled;
	wifi_display_update_wfd_ie(global);
}