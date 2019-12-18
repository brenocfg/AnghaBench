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
struct upnp_wps_device_sm {int /*<<< orphan*/ * web_srv; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_server_deinit (int /*<<< orphan*/ *) ; 

void web_listener_stop(struct upnp_wps_device_sm *sm)
{
	http_server_deinit(sm->web_srv);
	sm->web_srv = NULL;
}