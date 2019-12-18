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
struct wps_ap_pin_data {int timeout; int /*<<< orphan*/  pin_txt; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,struct wps_ap_pin_data*) ; 
 int os_snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  wps_ap_pin_set ; 

int hostapd_wps_ap_pin_set(struct hostapd_data *hapd, const char *pin,
			   int timeout)
{
	struct wps_ap_pin_data data;
	int ret;

	ret = os_snprintf(data.pin_txt, sizeof(data.pin_txt), "%s", pin);
	if (os_snprintf_error(sizeof(data.pin_txt), ret))
		return -1;
	data.timeout = timeout;
	return hostapd_wps_for_each(hapd, wps_ap_pin_set, &data);
}