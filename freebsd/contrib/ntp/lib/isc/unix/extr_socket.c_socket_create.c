#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_sockettype_t ;
typedef  int /*<<< orphan*/  isc_socketmgr_t ;
typedef  int /*<<< orphan*/  isc_socketmethods_t ;
typedef  int /*<<< orphan*/  isc_socket_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_18__ {size_t maxfd; int /*<<< orphan*/  lock; int /*<<< orphan*/  socklist; int /*<<< orphan*/ * fdlock; int /*<<< orphan*/ * fdstate; TYPE_5__** fds; int /*<<< orphan*/  stats; } ;
typedef  TYPE_4__ isc__socketmgr_t ;
struct TYPE_15__ {int /*<<< orphan*/ * methods; } ;
struct TYPE_19__ {int type; int pf; int references; size_t fd; TYPE_3__* manager; TYPE_1__ common; int /*<<< orphan*/ * statsindex; } ;
typedef  TYPE_5__ isc__socket_t ;
struct TYPE_17__ {TYPE_2__* fdpollinfo; } ;
struct TYPE_16__ {scalar_t__ want_read; scalar_t__ want_write; } ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  CREATION ; 
 int FDLOCK_ID (size_t) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_MSGSET_SOCKET ; 
 int /*<<< orphan*/  ISC_MSG_CREATED ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MANAGED ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 size_t STATID_OPENFAIL ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_MANAGER (TYPE_4__*) ; 
 scalar_t__ allocate_socket (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  free_socket (TYPE_5__**) ; 
 int /*<<< orphan*/  inc_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  isc_sockettype_fdwatch ; 
#define  isc_sockettype_tcp 130 
#define  isc_sockettype_udp 129 
#define  isc_sockettype_unix 128 
 int /*<<< orphan*/  link ; 
 scalar_t__ opensocket (TYPE_4__*,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  socket_log (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  socketmethods ; 
 int /*<<< orphan*/ * tcp4statsindex ; 
 int /*<<< orphan*/ * tcp6statsindex ; 
 int /*<<< orphan*/ * unixstatsindex ; 
 int /*<<< orphan*/ * upd4statsindex ; 
 int /*<<< orphan*/ * upd6statsindex ; 

__attribute__((used)) static isc_result_t
socket_create(isc_socketmgr_t *manager0, int pf, isc_sockettype_t type,
	      isc_socket_t **socketp, isc_socket_t *dup_socket)
{
	isc__socket_t *sock = NULL;
	isc__socketmgr_t *manager = (isc__socketmgr_t *)manager0;
	isc_result_t result;
	int lockid;

	REQUIRE(VALID_MANAGER(manager));
	REQUIRE(socketp != NULL && *socketp == NULL);
	REQUIRE(type != isc_sockettype_fdwatch);

	result = allocate_socket(manager, type, &sock);
	if (result != ISC_R_SUCCESS)
		return (result);

	switch (sock->type) {
	case isc_sockettype_udp:
		sock->statsindex =
			(pf == AF_INET) ? upd4statsindex : upd6statsindex;
		break;
	case isc_sockettype_tcp:
		sock->statsindex =
			(pf == AF_INET) ? tcp4statsindex : tcp6statsindex;
		break;
	case isc_sockettype_unix:
		sock->statsindex = unixstatsindex;
		break;
	default:
		INSIST(0);
	}

	sock->pf = pf;

	result = opensocket(manager, sock, (isc__socket_t *)dup_socket);
	if (result != ISC_R_SUCCESS) {
		inc_stats(manager->stats, sock->statsindex[STATID_OPENFAIL]);
		free_socket(&sock);
		return (result);
	}

	sock->common.methods = (isc_socketmethods_t *)&socketmethods;
	sock->references = 1;
	*socketp = (isc_socket_t *)sock;

	/*
	 * Note we don't have to lock the socket like we normally would because
	 * there are no external references to it yet.
	 */

	lockid = FDLOCK_ID(sock->fd);
	LOCK(&manager->fdlock[lockid]);
	manager->fds[sock->fd] = sock;
	manager->fdstate[sock->fd] = MANAGED;
#ifdef USE_DEVPOLL
	INSIST(sock->manager->fdpollinfo[sock->fd].want_read == 0 &&
	       sock->manager->fdpollinfo[sock->fd].want_write == 0);
#endif
	UNLOCK(&manager->fdlock[lockid]);

	LOCK(&manager->lock);
	ISC_LIST_APPEND(manager->socklist, sock, link);
#ifdef USE_SELECT
	if (manager->maxfd < sock->fd)
		manager->maxfd = sock->fd;
#endif
	UNLOCK(&manager->lock);

	socket_log(sock, NULL, CREATION, isc_msgcat, ISC_MSGSET_SOCKET,
		   ISC_MSG_CREATED, dup_socket == NULL ? "dupped" : "created");

	return (ISC_R_SUCCESS);
}