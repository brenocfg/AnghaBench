#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
struct TYPE_12__ {int /*<<< orphan*/  result; int /*<<< orphan*/  attributes; int /*<<< orphan*/ * ev_sender; } ;
typedef  TYPE_1__ isc_socketevent_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  scalar_t__ isc_boolean_t ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  recv_list; int /*<<< orphan*/  fd; int /*<<< orphan*/  manager; int /*<<< orphan*/  pending_recv; } ;
typedef  TYPE_2__ isc__socket_t ;

/* Variables and functions */
#define  DOIO_EOF 131 
#define  DOIO_HARD 130 
#define  DOIO_SOFT 129 
#define  DOIO_SUCCESS 128 
 int /*<<< orphan*/  EVENT ; 
 scalar_t__ ISC_FALSE ; 
 scalar_t__ ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_ENQUEUE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_EOF ; 
 int /*<<< orphan*/  ISC_R_INPROGRESS ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_SOCKEVENTATTR_ATTACHED ; 
 unsigned int ISC_SOCKFLAG_IMMEDIATE ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SELECT_POKE_READ ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int doio_recv (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ev_link ; 
 scalar_t__ isc_sockettype_udp ; 
 int /*<<< orphan*/  isc_task_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  select_poke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_recvdone_event (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  socket_log (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_result_t
socket_recv(isc__socket_t *sock, isc_socketevent_t *dev, isc_task_t *task,
	    unsigned int flags)
{
	int io_state;
	isc_boolean_t have_lock = ISC_FALSE;
	isc_task_t *ntask = NULL;
	isc_result_t result = ISC_R_SUCCESS;

	dev->ev_sender = task;

	if (sock->type == isc_sockettype_udp) {
		io_state = doio_recv(sock, dev);
	} else {
		LOCK(&sock->lock);
		have_lock = ISC_TRUE;

		if (ISC_LIST_EMPTY(sock->recv_list))
			io_state = doio_recv(sock, dev);
		else
			io_state = DOIO_SOFT;
	}

	switch (io_state) {
	case DOIO_SOFT:
		/*
		 * We couldn't read all or part of the request right now, so
		 * queue it.
		 *
		 * Attach to socket and to task
		 */
		isc_task_attach(task, &ntask);
		dev->attributes |= ISC_SOCKEVENTATTR_ATTACHED;

		if (!have_lock) {
			LOCK(&sock->lock);
			have_lock = ISC_TRUE;
		}

		/*
		 * Enqueue the request.  If the socket was previously not being
		 * watched, poke the watcher to start paying attention to it.
		 */
		if (ISC_LIST_EMPTY(sock->recv_list) && !sock->pending_recv)
			select_poke(sock->manager, sock->fd, SELECT_POKE_READ);
		ISC_LIST_ENQUEUE(sock->recv_list, dev, ev_link);

		socket_log(sock, NULL, EVENT, NULL, 0, 0,
			   "socket_recv: event %p -> task %p",
			   dev, ntask);

		if ((flags & ISC_SOCKFLAG_IMMEDIATE) != 0)
			result = ISC_R_INPROGRESS;
		break;

	case DOIO_EOF:
		dev->result = ISC_R_EOF;
		/* fallthrough */

	case DOIO_HARD:
	case DOIO_SUCCESS:
		if ((flags & ISC_SOCKFLAG_IMMEDIATE) == 0)
			send_recvdone_event(sock, &dev);
		break;
	}

	if (have_lock)
		UNLOCK(&sock->lock);

	return (result);
}