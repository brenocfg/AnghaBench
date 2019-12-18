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
struct eapol_sm {int timer_tick_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eapol_port_timers_tick ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_sm*) ; 
 scalar_t__ eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eapol_enable_timer_tick(struct eapol_sm *sm)
{
	if (sm->timer_tick_enabled)
		return;
	wpa_printf(MSG_DEBUG, "EAPOL: enable timer tick");
	eloop_cancel_timeout(eapol_port_timers_tick, NULL, sm);
	if (eloop_register_timeout(1, 0, eapol_port_timers_tick, NULL, sm) == 0)
		sm->timer_tick_enabled = 1;
}