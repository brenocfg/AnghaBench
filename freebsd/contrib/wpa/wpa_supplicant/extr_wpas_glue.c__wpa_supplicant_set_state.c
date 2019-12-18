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
typedef  enum wpa_states { ____Placeholder_wpa_states } wpa_states ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_supplicant_set_state (void*,int) ; 

__attribute__((used)) static void _wpa_supplicant_set_state(void *wpa_s, enum wpa_states state)
{
	wpa_supplicant_set_state(wpa_s, state);
}