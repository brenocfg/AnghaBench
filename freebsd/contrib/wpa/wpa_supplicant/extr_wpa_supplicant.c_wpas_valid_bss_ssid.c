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
struct wpa_supplicant {int dummy; } ;
struct wpa_ssid {int dummy; } ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_valid_bss (struct wpa_supplicant*,struct wpa_bss*) ; 
 scalar_t__ wpas_valid_ssid (struct wpa_supplicant*,struct wpa_ssid*) ; 

int wpas_valid_bss_ssid(struct wpa_supplicant *wpa_s, struct wpa_bss *test_bss,
			struct wpa_ssid *test_ssid)
{
	if (test_bss && !wpas_valid_bss(wpa_s, test_bss))
		return 0;

	return test_ssid == NULL || wpas_valid_ssid(wpa_s, test_ssid);
}