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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_state_machine {int /*<<< orphan*/  auth_alg; } ;

/* Variables and functions */

void wpa_auth_set_auth_alg(struct wpa_state_machine *sm, u16 auth_alg)
{
	if (sm)
		sm->auth_alg = auth_alg;
}