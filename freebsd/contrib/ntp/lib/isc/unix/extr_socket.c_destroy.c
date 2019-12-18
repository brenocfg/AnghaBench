#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  shutdown_ok; int /*<<< orphan*/  socklist; scalar_t__ maxsocks; } ;
typedef  TYPE_1__ isc__socketmgr_t ;
struct TYPE_10__ {int fd; int /*<<< orphan*/ * connect_ev; int /*<<< orphan*/  send_list; int /*<<< orphan*/  recv_list; int /*<<< orphan*/  accept_list; TYPE_1__* manager; } ;
typedef  TYPE_2__ isc__socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  CREATION ; 
 int /*<<< orphan*/  INSIST (scalar_t__) ; 
 scalar_t__ ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_MSGSET_SOCKET ; 
 int /*<<< orphan*/  ISC_MSG_DESTROYING ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  SIGNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  free_socket (TYPE_2__**) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  socket_log (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
destroy(isc__socket_t **sockp) {
	int fd;
	isc__socket_t *sock = *sockp;
	isc__socketmgr_t *manager = sock->manager;

	socket_log(sock, NULL, CREATION, isc_msgcat, ISC_MSGSET_SOCKET,
		   ISC_MSG_DESTROYING, "destroying");

	INSIST(ISC_LIST_EMPTY(sock->accept_list));
	INSIST(ISC_LIST_EMPTY(sock->recv_list));
	INSIST(ISC_LIST_EMPTY(sock->send_list));
	INSIST(sock->connect_ev == NULL);
	REQUIRE(sock->fd == -1 || sock->fd < (int)manager->maxsocks);

	if (sock->fd >= 0) {
		fd = sock->fd;
		sock->fd = -1;
		closesocket(manager, sock, fd);
	}

	LOCK(&manager->lock);

	ISC_LIST_UNLINK(manager->socklist, sock, link);

#ifdef USE_WATCHER_THREAD
	if (ISC_LIST_EMPTY(manager->socklist))
		SIGNAL(&manager->shutdown_ok);
#endif /* USE_WATCHER_THREAD */

	/* can't unlock manager as its memory context is still used */
	free_socket(sockp);

	UNLOCK(&manager->lock);
}