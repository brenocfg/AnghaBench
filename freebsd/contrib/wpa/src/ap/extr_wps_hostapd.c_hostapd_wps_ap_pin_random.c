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
struct wps_ap_pin_data {int timeout; int /*<<< orphan*/  pin_txt; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {char const* ap_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,struct wps_ap_pin_data*) ; 
 int /*<<< orphan*/  os_snprintf (int /*<<< orphan*/ ,int,char*,unsigned int) ; 
 int /*<<< orphan*/  wps_ap_pin_set ; 
 scalar_t__ wps_generate_pin (unsigned int*) ; 

const char * hostapd_wps_ap_pin_random(struct hostapd_data *hapd, int timeout)
{
	unsigned int pin;
	struct wps_ap_pin_data data;

	if (wps_generate_pin(&pin) < 0)
		return NULL;
	os_snprintf(data.pin_txt, sizeof(data.pin_txt), "%08u", pin);
	data.timeout = timeout;
	hostapd_wps_for_each(hapd, wps_ap_pin_set, &data);
	return hapd->conf->ap_pin;
}