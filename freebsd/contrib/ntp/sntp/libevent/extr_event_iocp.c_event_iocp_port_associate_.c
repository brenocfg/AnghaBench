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
struct event_iocp_port {int /*<<< orphan*/  n_threads; int /*<<< orphan*/  port; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_uintptr_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateIoCompletionPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
event_iocp_port_associate_(struct event_iocp_port *port, evutil_socket_t fd,
    ev_uintptr_t key)
{
	HANDLE h;
	h = CreateIoCompletionPort((HANDLE)fd, port->port, key, port->n_threads);
	if (!h)
		return -1;
	return 0;
}