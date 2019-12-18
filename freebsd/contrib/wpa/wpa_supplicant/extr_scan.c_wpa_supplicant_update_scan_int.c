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
struct wpa_supplicant {int scan_interval; } ;
struct os_reltime {int sec; scalar_t__ usec; } ;

/* Variables and functions */
 int eloop_cancel_timeout_one (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *,struct os_reltime*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,scalar_t__,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_reltime_before (struct os_reltime*,struct os_reltime*) ; 
 int /*<<< orphan*/  wpa_supplicant_scan ; 

void wpa_supplicant_update_scan_int(struct wpa_supplicant *wpa_s, int sec)
{
	struct os_reltime remaining, new_int;
	int cancelled;

	cancelled = eloop_cancel_timeout_one(wpa_supplicant_scan, wpa_s, NULL,
					     &remaining);

	new_int.sec = sec;
	new_int.usec = 0;
	if (cancelled && os_reltime_before(&remaining, &new_int)) {
		new_int.sec = remaining.sec;
		new_int.usec = remaining.usec;
	}

	if (cancelled) {
		eloop_register_timeout(new_int.sec, new_int.usec,
				       wpa_supplicant_scan, wpa_s, NULL);
	}
	wpa_s->scan_interval = sec;
}