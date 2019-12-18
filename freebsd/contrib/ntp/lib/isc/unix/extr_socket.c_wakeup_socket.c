#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_5__ {scalar_t__* fdstate; int /*<<< orphan*/ * fdlock; scalar_t__ maxsocks; } ;
typedef  TYPE_1__ isc__socketmgr_t ;

/* Variables and functions */
 scalar_t__ CLOSED ; 
 scalar_t__ CLOSE_PENDING ; 
 int FDLOCK_ID (int) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_LOGCATEGORY_GENERAL ; 
 int /*<<< orphan*/  ISC_LOGMODULE_SOCKET ; 
 int /*<<< orphan*/  ISC_LOG_ERROR ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ MANAGED ; 
 int SELECT_POKE_CLOSE ; 
 int /*<<< orphan*/  SELECT_POKE_READ ; 
 int /*<<< orphan*/  SELECT_POKE_WRITE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  isc_lctx ; 
 int /*<<< orphan*/  isc_log_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_result_totext (scalar_t__) ; 
 int /*<<< orphan*/  unwatch_fd (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ watch_fd (TYPE_1__*,int,int) ; 

__attribute__((used)) static void
wakeup_socket(isc__socketmgr_t *manager, int fd, int msg) {
	isc_result_t result;
	int lockid = FDLOCK_ID(fd);

	/*
	 * This is a wakeup on a socket.  If the socket is not in the
	 * process of being closed, start watching it for either reads
	 * or writes.
	 */

	INSIST(fd >= 0 && fd < (int)manager->maxsocks);

	if (msg == SELECT_POKE_CLOSE) {
		/* No one should be updating fdstate, so no need to lock it */
		INSIST(manager->fdstate[fd] == CLOSE_PENDING);
		manager->fdstate[fd] = CLOSED;
		(void)unwatch_fd(manager, fd, SELECT_POKE_READ);
		(void)unwatch_fd(manager, fd, SELECT_POKE_WRITE);
		(void)close(fd);
		return;
	}

	LOCK(&manager->fdlock[lockid]);
	if (manager->fdstate[fd] == CLOSE_PENDING) {
		UNLOCK(&manager->fdlock[lockid]);

		/*
		 * We accept (and ignore) any error from unwatch_fd() as we are
		 * closing the socket, hoping it doesn't leave dangling state in
		 * the kernel.
		 * Note that unwatch_fd() must be called after releasing the
		 * fdlock; otherwise it could cause deadlock due to a lock order
		 * reversal.
		 */
		(void)unwatch_fd(manager, fd, SELECT_POKE_READ);
		(void)unwatch_fd(manager, fd, SELECT_POKE_WRITE);
		return;
	}
	if (manager->fdstate[fd] != MANAGED) {
		UNLOCK(&manager->fdlock[lockid]);
		return;
	}
	UNLOCK(&manager->fdlock[lockid]);

	/*
	 * Set requested bit.
	 */
	result = watch_fd(manager, fd, msg);
	if (result != ISC_R_SUCCESS) {
		/*
		 * XXXJT: what should we do?  Ignoring the failure of watching
		 * a socket will make the application dysfunctional, but there
		 * seems to be no reasonable recovery process.
		 */
		isc_log_write(isc_lctx, ISC_LOGCATEGORY_GENERAL,
			      ISC_LOGMODULE_SOCKET, ISC_LOG_ERROR,
			      "failed to start watching FD (%d): %s",
			      fd, isc_result_totext(result));
	}
}