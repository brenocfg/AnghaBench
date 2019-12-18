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

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_supplicant_update_scan_int (struct wpa_supplicant*,int) ; 

int wpa_supplicant_set_scan_interval(struct wpa_supplicant *wpa_s,
				     int scan_interval)
{
	if (scan_interval < 0) {
		wpa_msg(wpa_s, MSG_ERROR, "Invalid scan interval %d",
			scan_interval);
		return -1;
	}
	wpa_msg(wpa_s, MSG_DEBUG, "Setting scan interval: %d sec",
		scan_interval);
	wpa_supplicant_update_scan_int(wpa_s, scan_interval);

	return 0;
}