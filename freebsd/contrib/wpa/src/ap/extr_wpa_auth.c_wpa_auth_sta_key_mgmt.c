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
struct wpa_state_machine {int wpa_key_mgmt; } ;

/* Variables and functions */

int wpa_auth_sta_key_mgmt(struct wpa_state_machine *sm)
{
	if (sm == NULL)
		return -1;
	return sm->wpa_key_mgmt;
}