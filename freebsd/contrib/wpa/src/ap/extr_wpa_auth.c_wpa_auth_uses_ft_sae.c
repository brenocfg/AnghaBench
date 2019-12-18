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
struct wpa_state_machine {scalar_t__ wpa_key_mgmt; } ;

/* Variables and functions */
 scalar_t__ WPA_KEY_MGMT_FT_SAE ; 

int wpa_auth_uses_ft_sae(struct wpa_state_machine *sm)
{
	if (sm == NULL)
		return 0;
	return sm->wpa_key_mgmt == WPA_KEY_MGMT_FT_SAE;
}