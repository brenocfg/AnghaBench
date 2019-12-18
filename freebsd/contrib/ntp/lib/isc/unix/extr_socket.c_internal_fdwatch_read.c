#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_socket_t ;
struct TYPE_8__ {scalar_t__ ev_type; scalar_t__ ev_sender; } ;
typedef  TYPE_1__ isc_event_t ;
struct TYPE_9__ {int pending_recv; int (* fdwatchcb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ references; int /*<<< orphan*/  lock; int /*<<< orphan*/  fd; int /*<<< orphan*/  manager; int /*<<< orphan*/  fdwatcharg; } ;
typedef  TYPE_2__ isc__socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  IOEVENT ; 
 int /*<<< orphan*/  ISC_MSGSET_SOCKET ; 
 int /*<<< orphan*/  ISC_MSG_INTERNALRECV ; 
 scalar_t__ ISC_SOCKEVENT_INTR ; 
 int /*<<< orphan*/  ISC_SOCKFDWATCH_READ ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SELECT_POKE_READ ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_SOCKET (TYPE_2__*) ; 
 int /*<<< orphan*/  destroy (TYPE_2__**) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  select_poke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_log (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
internal_fdwatch_read(isc_task_t *me, isc_event_t *ev) {
	isc__socket_t *sock;
	int more_data;

	INSIST(ev->ev_type == ISC_SOCKEVENT_INTR);

	/*
	 * Find out what socket this is and lock it.
	 */
	sock = (isc__socket_t *)ev->ev_sender;
	INSIST(VALID_SOCKET(sock));

	LOCK(&sock->lock);
	socket_log(sock, NULL, IOEVENT,
		   isc_msgcat, ISC_MSGSET_SOCKET, ISC_MSG_INTERNALRECV,
		   "internal_fdwatch_read: task %p got event %p", me, ev);

	INSIST(sock->pending_recv == 1);

	UNLOCK(&sock->lock);
	more_data = (sock->fdwatchcb)(me, (isc_socket_t *)sock,
				      sock->fdwatcharg, ISC_SOCKFDWATCH_READ);
	LOCK(&sock->lock);

	sock->pending_recv = 0;

	INSIST(sock->references > 0);
	sock->references--;  /* the internal event is done with this socket */
	if (sock->references == 0) {
		UNLOCK(&sock->lock);
		destroy(&sock);
		return;
	}

	if (more_data)
		select_poke(sock->manager, sock->fd, SELECT_POKE_READ);

	UNLOCK(&sock->lock);
}