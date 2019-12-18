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
struct wpa_state_machine {int tk_already_set; int /*<<< orphan*/  wpa_key_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 

int wpa_auth_sta_ft_tk_already_set(struct wpa_state_machine *sm)
{
	if (!sm || !wpa_key_mgmt_ft(sm->wpa_key_mgmt))
		return 0;
	return sm->tk_already_set;
}