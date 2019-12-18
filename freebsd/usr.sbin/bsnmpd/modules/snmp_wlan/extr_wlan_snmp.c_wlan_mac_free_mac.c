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
struct wlan_mac_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct wlan_mac_mac*) ; 

void
wlan_mac_free_mac(struct wlan_mac_mac *wmm)
{
	free(wmm);
}