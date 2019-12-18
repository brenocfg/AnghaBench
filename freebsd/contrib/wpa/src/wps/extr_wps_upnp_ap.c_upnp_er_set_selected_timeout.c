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
struct wps_registrar {int dummy; } ;
struct subscription {scalar_t__ selected_registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void upnp_er_set_selected_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct subscription *s = eloop_ctx;
	struct wps_registrar *reg = timeout_ctx;
	wpa_printf(MSG_DEBUG, "WPS: SetSelectedRegistrar from ER timed out");
	s->selected_registrar = 0;
	wps_registrar_selected_registrar_changed(reg, 0);
}