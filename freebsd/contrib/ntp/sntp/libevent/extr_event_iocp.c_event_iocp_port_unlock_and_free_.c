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
struct event_iocp_port {struct event_iocp_port* threads; int /*<<< orphan*/  shutdownSemaphore; int /*<<< orphan*/  port; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct event_iocp_port*) ; 

__attribute__((used)) static void
event_iocp_port_unlock_and_free_(struct event_iocp_port *port)
{
	DeleteCriticalSection(&port->lock);
	CloseHandle(port->port);
	CloseHandle(port->shutdownSemaphore);
	mm_free(port->threads);
	mm_free(port);
}