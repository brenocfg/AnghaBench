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
struct event_iocp_port {long ms; scalar_t__ n_live_threads; int /*<<< orphan*/  lock; int /*<<< orphan*/  shutdownSemaphore; scalar_t__ shutdown; int /*<<< orphan*/  port; } ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  OVERLAPPED ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int GetQueuedCompletionStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ **,long) ; 
 long INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ NOTIFICATION_KEY ; 
 int /*<<< orphan*/  ReleaseSemaphore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_warnx (char*) ; 
 int /*<<< orphan*/  handle_entry (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
loop(void *port_)
{
	struct event_iocp_port *port = port_;
	long ms = port->ms;
	HANDLE p = port->port;

	if (ms <= 0)
		ms = INFINITE;

	while (1) {
		OVERLAPPED *overlapped=NULL;
		ULONG_PTR key=0;
		DWORD bytes=0;
		int ok = GetQueuedCompletionStatus(p, &bytes, &key,
			&overlapped, ms);
		EnterCriticalSection(&port->lock);
		if (port->shutdown) {
			if (--port->n_live_threads == 0)
				ReleaseSemaphore(port->shutdownSemaphore, 1,
						NULL);
			LeaveCriticalSection(&port->lock);
			return;
		}
		LeaveCriticalSection(&port->lock);

		if (key != NOTIFICATION_KEY && overlapped)
			handle_entry(overlapped, key, bytes, ok);
		else if (!overlapped)
			break;
	}
	event_warnx("GetQueuedCompletionStatus exited with no event.");
	EnterCriticalSection(&port->lock);
	if (--port->n_live_threads == 0)
		ReleaseSemaphore(port->shutdownSemaphore, 1, NULL);
	LeaveCriticalSection(&port->lock);
}