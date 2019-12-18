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
struct interface {scalar_t__ fd; int flags; scalar_t__ last_ttl; int /*<<< orphan*/  sin; } ;

/* Variables and functions */
 int INT_BCASTXMIT ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  close_and_delete_fd_from_list (scalar_t__) ; 
 scalar_t__ open_socket (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct interface*) ; 
 int /*<<< orphan*/  socket_broadcast_disable (struct interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
refresh_interface(
	struct interface * interface
	)
{
#ifdef  OS_MISSES_SPECIFIC_ROUTE_UPDATES
	if (interface->fd != INVALID_SOCKET) {
		int bcast = (interface->flags & INT_BCASTXMIT) != 0;
		/* as we forcibly close() the socket remove the
		   broadcast permission indication */
		if (bcast)
			socket_broadcast_disable(interface, &interface->sin);

		close_and_delete_fd_from_list(interface->fd);

		/* create new socket picking up a new first hop binding
		   at connect() time */
		interface->fd = open_socket(&interface->sin,
					    bcast, 0, interface);
		 /*
		  * reset TTL indication so TTL is is set again
		  * next time around
		  */
		interface->last_ttl = 0;
		return (interface->fd != INVALID_SOCKET);
	} else
		return 0;	/* invalid sockets are not refreshable */
#else /* !OS_MISSES_SPECIFIC_ROUTE_UPDATES */
	return (interface->fd != INVALID_SOCKET);
#endif /* !OS_MISSES_SPECIFIC_ROUTE_UPDATES */
}