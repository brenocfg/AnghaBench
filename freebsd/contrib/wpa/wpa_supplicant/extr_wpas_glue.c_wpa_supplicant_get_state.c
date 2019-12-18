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
struct wpa_supplicant {int wpa_state; } ;
typedef  enum wpa_states { ____Placeholder_wpa_states } wpa_states ;

/* Variables and functions */

__attribute__((used)) static enum wpa_states wpa_supplicant_get_state(struct wpa_supplicant *wpa_s)
{
	return wpa_s->wpa_state;
}