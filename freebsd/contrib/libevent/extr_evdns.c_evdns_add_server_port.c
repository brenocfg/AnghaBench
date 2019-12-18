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
struct evdns_server_port {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  evdns_request_callback_fn_type ;

/* Variables and functions */
 struct evdns_server_port* evdns_add_server_port_with_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

struct evdns_server_port *
evdns_add_server_port(evutil_socket_t socket, int flags, evdns_request_callback_fn_type cb, void *user_data)
{
	return evdns_add_server_port_with_base(NULL, socket, flags, cb, user_data);
}