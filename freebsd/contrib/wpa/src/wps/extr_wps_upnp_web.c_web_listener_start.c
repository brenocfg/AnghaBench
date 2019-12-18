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
struct upnp_wps_device_sm {int /*<<< orphan*/ * web_srv; int /*<<< orphan*/  web_port; int /*<<< orphan*/  ip_addr; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_server_get_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * http_server_init (struct in_addr*,int,int /*<<< orphan*/ ,struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  web_connection_check_data ; 
 int /*<<< orphan*/  web_listener_stop (struct upnp_wps_device_sm*) ; 

int web_listener_start(struct upnp_wps_device_sm *sm)
{
	struct in_addr addr;
	addr.s_addr = sm->ip_addr;
	sm->web_srv = http_server_init(&addr, -1, web_connection_check_data,
				       sm);
	if (sm->web_srv == NULL) {
		web_listener_stop(sm);
		return -1;
	}
	sm->web_port = http_server_get_port(sm->web_srv);

	return 0;
}