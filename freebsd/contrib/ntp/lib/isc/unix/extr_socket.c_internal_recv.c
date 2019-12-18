#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
struct TYPE_14__ {int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ isc_socketevent_t ;
struct TYPE_15__ {scalar_t__ ev_type; TYPE_3__* ev_sender; } ;
typedef  TYPE_2__ isc_event_t ;
struct TYPE_16__ {int pending_recv; scalar_t__ references; int /*<<< orphan*/  lock; int /*<<< orphan*/  fd; int /*<<< orphan*/  manager; int /*<<< orphan*/  recv_list; } ;
typedef  TYPE_3__ isc__socket_t ;

/* Variables and functions */
#define  DOIO_EOF 131 
#define  DOIO_HARD 130 
#define  DOIO_SOFT 129 
#define  DOIO_SUCCESS 128 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  IOEVENT ; 
 int /*<<< orphan*/  ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_MSGSET_SOCKET ; 
 int /*<<< orphan*/  ISC_MSG_INTERNALRECV ; 
 int /*<<< orphan*/  ISC_R_EOF ; 
 scalar_t__ ISC_SOCKEVENT_INTR ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SELECT_POKE_READ ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_SOCKET (TYPE_3__*) ; 
 int /*<<< orphan*/  destroy (TYPE_3__**) ; 
 int doio_recv (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  select_poke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_recvdone_event (TYPE_3__*,TYPE_1__**) ; 
 int /*<<< orphan*/  socket_log (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
internal_recv(isc_task_t *me, isc_event_t *ev) {
	isc_socketevent_t *dev;
	isc__socket_t *sock;

	INSIST(ev->ev_type == ISC_SOCKEVENT_INTR);

	sock = ev->ev_sender;
	INSIST(VALID_SOCKET(sock));

	LOCK(&sock->lock);
	socket_log(sock, NULL, IOEVENT,
		   isc_msgcat, ISC_MSGSET_SOCKET, ISC_MSG_INTERNALRECV,
		   "internal_recv: task %p got event %p", me, ev);

	INSIST(sock->pending_recv == 1);
	sock->pending_recv = 0;

	INSIST(sock->references > 0);
	sock->references--;  /* the internal event is done with this socket */
	if (sock->references == 0) {
		UNLOCK(&sock->lock);
		destroy(&sock);
		return;
	}

	/*
	 * Try to do as much I/O as possible on this socket.  There are no
	 * limits here, currently.
	 */
	dev = ISC_LIST_HEAD(sock->recv_list);
	while (dev != NULL) {
		switch (doio_recv(sock, dev)) {
		case DOIO_SOFT:
			goto poke;

		case DOIO_EOF:
			/*
			 * read of 0 means the remote end was closed.
			 * Run through the event queue and dispatch all
			 * the events with an EOF result code.
			 */
			do {
				dev->result = ISC_R_EOF;
				send_recvdone_event(sock, &dev);
				dev = ISC_LIST_HEAD(sock->recv_list);
			} while (dev != NULL);
			goto poke;

		case DOIO_SUCCESS:
		case DOIO_HARD:
			send_recvdone_event(sock, &dev);
			break;
		}

		dev = ISC_LIST_HEAD(sock->recv_list);
	}

 poke:
	if (!ISC_LIST_EMPTY(sock->recv_list))
		select_poke(sock->manager, sock->fd, SELECT_POKE_READ);

	UNLOCK(&sock->lock);
}