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
struct event_iocp_port {int shutdown; int n_live_threads; int /*<<< orphan*/  lock; int /*<<< orphan*/  shutdownSemaphore; } ;
typedef  long DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 long INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  event_iocp_notify_all (struct event_iocp_port*) ; 
 int /*<<< orphan*/  event_iocp_port_unlock_and_free_ (struct event_iocp_port*) ; 

int
event_iocp_shutdown_(struct event_iocp_port *port, long waitMsec)
{
	DWORD ms = INFINITE;
	int n;

	EnterCriticalSection(&port->lock);
	port->shutdown = 1;
	LeaveCriticalSection(&port->lock);
	event_iocp_notify_all(port);

	if (waitMsec >= 0)
		ms = waitMsec;

	WaitForSingleObject(port->shutdownSemaphore, ms);
	EnterCriticalSection(&port->lock);
	n = port->n_live_threads;
	LeaveCriticalSection(&port->lock);
	if (n == 0) {
		event_iocp_port_unlock_and_free_(port);
		return 0;
	} else {
		return -1;
	}
}