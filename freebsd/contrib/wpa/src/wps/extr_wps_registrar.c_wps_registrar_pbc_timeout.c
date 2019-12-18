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
struct wps_registrar {int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_pbc_timeout_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_stop_pbc (struct wps_registrar*) ; 

__attribute__((used)) static void wps_registrar_pbc_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wps_registrar *reg = eloop_ctx;

	wpa_printf(MSG_DEBUG, "WPS: PBC timed out - disable PBC mode");
	wps_pbc_timeout_event(reg->wps);
	wps_registrar_stop_pbc(reg);
}