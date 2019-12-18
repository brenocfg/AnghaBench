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
struct upnp_wps_device_sm {scalar_t__ multicast_sd; int /*<<< orphan*/  ip_addr; } ;

/* Variables and functions */
 scalar_t__ ssdp_open_multicast_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ssdp_open_multicast(struct upnp_wps_device_sm *sm)
{
	sm->multicast_sd = ssdp_open_multicast_sock(sm->ip_addr, NULL);
	if (sm->multicast_sd < 0)
		return -1;
	return 0;
}