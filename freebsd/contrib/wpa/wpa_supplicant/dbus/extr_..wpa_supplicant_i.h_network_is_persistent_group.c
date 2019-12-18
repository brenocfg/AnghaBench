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
struct wpa_ssid {int disabled; scalar_t__ p2p_persistent_group; } ;

/* Variables and functions */

__attribute__((used)) static inline int network_is_persistent_group(struct wpa_ssid *ssid)
{
	return ssid->disabled == 2 && ssid->p2p_persistent_group;
}