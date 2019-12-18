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
struct wps_registrar {scalar_t__ pbc; scalar_t__ selected_registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wps_registrar_set_selected_timeout(void *eloop_ctx,
					       void *timeout_ctx)
{
	struct wps_registrar *reg = eloop_ctx;

	wpa_printf(MSG_DEBUG, "WPS: Selected Registrar timeout - "
		   "unselect internal Registrar");
	reg->selected_registrar = 0;
	reg->pbc = 0;
	wps_registrar_selected_registrar_changed(reg, 0);
}