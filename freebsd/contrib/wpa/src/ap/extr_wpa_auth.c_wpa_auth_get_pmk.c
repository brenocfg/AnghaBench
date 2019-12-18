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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_state_machine {int pmk_len; int /*<<< orphan*/  const* PMK; } ;

/* Variables and functions */

const u8 * wpa_auth_get_pmk(struct wpa_state_machine *sm, int *len)
{
	if (!sm)
		return NULL;
	*len = sm->pmk_len;
	return sm->PMK;
}