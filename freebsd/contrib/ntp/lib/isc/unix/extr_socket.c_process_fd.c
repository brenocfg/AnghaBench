#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_boolean_t ;
struct TYPE_10__ {scalar_t__* fdstate; int /*<<< orphan*/ * fdlock; TYPE_2__** fds; } ;
typedef  TYPE_1__ isc__socketmgr_t ;
struct TYPE_11__ {int /*<<< orphan*/  lock; scalar_t__ connecting; scalar_t__ listener; } ;
typedef  TYPE_2__ isc__socket_t ;

/* Variables and functions */
 scalar_t__ CLOSE_PENDING ; 
 int FDLOCK_ID (int) ; 
 scalar_t__ ISC_FALSE ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SELECT_POKE_READ ; 
 int /*<<< orphan*/  SELECT_POKE_WRITE ; 
 int /*<<< orphan*/  SOCK_DEAD (TYPE_2__*) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch_accept (TYPE_2__*) ; 
 int /*<<< orphan*/  dispatch_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  dispatch_recv (TYPE_2__*) ; 
 int /*<<< orphan*/  dispatch_send (TYPE_2__*) ; 
 int /*<<< orphan*/  unwatch_fd (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_fd(isc__socketmgr_t *manager, int fd, isc_boolean_t readable,
	   isc_boolean_t writeable)
{
	isc__socket_t *sock;
	isc_boolean_t unlock_sock;
	isc_boolean_t unwatch_read = ISC_FALSE, unwatch_write = ISC_FALSE;
	int lockid = FDLOCK_ID(fd);

	/*
	 * If the socket is going to be closed, don't do more I/O.
	 */
	LOCK(&manager->fdlock[lockid]);
	if (manager->fdstate[fd] == CLOSE_PENDING) {
		UNLOCK(&manager->fdlock[lockid]);

		(void)unwatch_fd(manager, fd, SELECT_POKE_READ);
		(void)unwatch_fd(manager, fd, SELECT_POKE_WRITE);
		return;
	}

	sock = manager->fds[fd];
	unlock_sock = ISC_FALSE;
	if (readable) {
		if (sock == NULL) {
			unwatch_read = ISC_TRUE;
			goto check_write;
		}
		unlock_sock = ISC_TRUE;
		LOCK(&sock->lock);
		if (!SOCK_DEAD(sock)) {
			if (sock->listener)
				dispatch_accept(sock);
			else
				dispatch_recv(sock);
		}
		unwatch_read = ISC_TRUE;
	}
check_write:
	if (writeable) {
		if (sock == NULL) {
			unwatch_write = ISC_TRUE;
			goto unlock_fd;
		}
		if (!unlock_sock) {
			unlock_sock = ISC_TRUE;
			LOCK(&sock->lock);
		}
		if (!SOCK_DEAD(sock)) {
			if (sock->connecting)
				dispatch_connect(sock);
			else
				dispatch_send(sock);
		}
		unwatch_write = ISC_TRUE;
	}
	if (unlock_sock)
		UNLOCK(&sock->lock);

 unlock_fd:
	UNLOCK(&manager->fdlock[lockid]);
	if (unwatch_read)
		(void)unwatch_fd(manager, fd, SELECT_POKE_READ);
	if (unwatch_write)
		(void)unwatch_fd(manager, fd, SELECT_POKE_WRITE);

}