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
struct upnp_wps_device_sm {int /*<<< orphan*/  subscriptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 

int upnp_wps_subscribers(struct upnp_wps_device_sm *sm)
{
	return !dl_list_empty(&sm->subscriptions);
}