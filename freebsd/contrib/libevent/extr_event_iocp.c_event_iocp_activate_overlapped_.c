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
struct event_overlapped {int /*<<< orphan*/  overlapped; } ;
struct event_iocp_port {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  ev_uintptr_t ;
typedef  int /*<<< orphan*/  ev_uint32_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ PostQueuedCompletionStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
event_iocp_activate_overlapped_(
    struct event_iocp_port *port, struct event_overlapped *o,
    ev_uintptr_t key, ev_uint32_t n)
{
	BOOL r;

	r = PostQueuedCompletionStatus(port->port, n, key, &o->overlapped);
	return (r==0) ? -1 : 0;
}