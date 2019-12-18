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
struct wps_registrar {scalar_t__ selected_registrar; scalar_t__ pbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/  (*) (struct wps_registrar*,int /*<<< orphan*/ *),struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_registrar_invalidate_wildcard_pin (struct wps_registrar*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_pbc_timeout (struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_registrar_pin_completed (struct wps_registrar*) ; 

int wps_registrar_wps_cancel(struct wps_registrar *reg)
{
	if (reg->pbc) {
		wpa_printf(MSG_DEBUG, "WPS: PBC is set - cancelling it");
		wps_registrar_pbc_timeout(reg, NULL);
		eloop_cancel_timeout(wps_registrar_pbc_timeout, reg, NULL);
		return 1;
	} else if (reg->selected_registrar) {
		/* PIN Method */
		wpa_printf(MSG_DEBUG, "WPS: PIN is set - cancelling it");
		wps_registrar_pin_completed(reg);
		wps_registrar_invalidate_wildcard_pin(reg, NULL, 0);
		return 1;
	}
	return 0;
}