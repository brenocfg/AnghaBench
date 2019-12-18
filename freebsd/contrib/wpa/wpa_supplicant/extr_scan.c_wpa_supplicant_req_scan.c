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
struct wpa_supplicant {scalar_t__ p2p_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int eloop_deplete_timeout (int,int,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  wpa_supplicant_scan ; 

void wpa_supplicant_req_scan(struct wpa_supplicant *wpa_s, int sec, int usec)
{
	int res;

	if (wpa_s->p2p_mgmt) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"Ignore scan request (%d.%06d sec) on p2p_mgmt interface",
			sec, usec);
		return;
	}

	res = eloop_deplete_timeout(sec, usec, wpa_supplicant_scan, wpa_s,
				    NULL);
	if (res == 1) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Rescheduling scan request: %d.%06d sec",
			sec, usec);
	} else if (res == 0) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Ignore new scan request for %d.%06d sec since an earlier request is scheduled to trigger sooner",
			sec, usec);
	} else {
		wpa_dbg(wpa_s, MSG_DEBUG, "Setting scan request: %d.%06d sec",
			sec, usec);
		eloop_register_timeout(sec, usec, wpa_supplicant_scan, wpa_s, NULL);
	}
}