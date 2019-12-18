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
struct hostapd_iface {scalar_t__ acs_num_completed_scans; TYPE_1__* conf; int /*<<< orphan*/ * bss; int /*<<< orphan*/ * scan_cb; } ;
struct TYPE_2__ {scalar_t__ acs_num_scans; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  acs_fail (struct hostapd_iface*) ; 
 int acs_request_scan (struct hostapd_iface*) ; 
 int /*<<< orphan*/  acs_study (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_acs_completed (struct hostapd_iface*,int) ; 
 int hostapd_drv_get_survey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void acs_scan_complete(struct hostapd_iface *iface)
{
	int err;

	iface->scan_cb = NULL;

	wpa_printf(MSG_DEBUG, "ACS: Using survey based algorithm (acs_num_scans=%d)",
		   iface->conf->acs_num_scans);

	err = hostapd_drv_get_survey(iface->bss[0], 0);
	if (err) {
		wpa_printf(MSG_ERROR, "ACS: Failed to get survey data");
		goto fail;
	}

	if (++iface->acs_num_completed_scans < iface->conf->acs_num_scans) {
		err = acs_request_scan(iface);
		if (err) {
			wpa_printf(MSG_ERROR, "ACS: Failed to request scan");
			goto fail;
		}

		return;
	}

	acs_study(iface);
	return;
fail:
	hostapd_acs_completed(iface, 1);
	acs_fail(iface);
}