#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* current_ssid; int /*<<< orphan*/  p2p_mgmt; } ;
struct TYPE_2__ {scalar_t__ p2p_persistent_group; scalar_t__ p2p_group; int /*<<< orphan*/  disabled; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int p2p_is_active_persistent_group(struct wpa_supplicant *wpa_s)
{
	return !wpa_s->p2p_mgmt && wpa_s->current_ssid &&
		!wpa_s->current_ssid->disabled &&
		wpa_s->current_ssid->p2p_group &&
		wpa_s->current_ssid->p2p_persistent_group;
}