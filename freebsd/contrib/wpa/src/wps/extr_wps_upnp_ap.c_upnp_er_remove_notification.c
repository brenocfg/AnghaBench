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
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct subscription*,struct wps_registrar*) ; 
 int /*<<< orphan*/  upnp_er_set_selected_timeout ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 

void upnp_er_remove_notification(struct wps_registrar *reg,
				 struct subscription *s)
{
	s->selected_registrar = 0;
	eloop_cancel_timeout(upnp_er_set_selected_timeout, s, reg);
	if (reg)
		wps_registrar_selected_registrar_changed(reg, 0);
}