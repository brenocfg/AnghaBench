#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ impmagic; scalar_t__ magic; } ;
struct TYPE_10__ {scalar_t__ references; int recvcmsgbuflen; int sendcmsgbuflen; TYPE_2__* manager; int /*<<< orphan*/  lock; TYPE_1__ common; struct TYPE_10__* sendcmsgbuf; struct TYPE_10__* recvcmsgbuf; int /*<<< orphan*/  accept_list; int /*<<< orphan*/  send_list; int /*<<< orphan*/  recv_list; int /*<<< orphan*/  pending_accept; int /*<<< orphan*/  pending_send; int /*<<< orphan*/  pending_recv; int /*<<< orphan*/  connecting; } ;
typedef  TYPE_3__ isc__socket_t ;
struct TYPE_9__ {int /*<<< orphan*/  mctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_LINK_LINKED (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 int VALID_SOCKET (TYPE_3__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
free_socket(isc__socket_t **socketp) {
	isc__socket_t *sock = *socketp;

	INSIST(sock->references == 0);
	INSIST(VALID_SOCKET(sock));
	INSIST(!sock->connecting);
	INSIST(!sock->pending_recv);
	INSIST(!sock->pending_send);
	INSIST(!sock->pending_accept);
	INSIST(ISC_LIST_EMPTY(sock->recv_list));
	INSIST(ISC_LIST_EMPTY(sock->send_list));
	INSIST(ISC_LIST_EMPTY(sock->accept_list));
	INSIST(!ISC_LINK_LINKED(sock, link));

	if (sock->recvcmsgbuf != NULL)
		isc_mem_put(sock->manager->mctx, sock->recvcmsgbuf,
			    sock->recvcmsgbuflen);
	if (sock->sendcmsgbuf != NULL)
		isc_mem_put(sock->manager->mctx, sock->sendcmsgbuf,
			    sock->sendcmsgbuflen);

	sock->common.magic = 0;
	sock->common.impmagic = 0;

	DESTROYLOCK(&sock->lock);

	isc_mem_put(sock->manager->mctx, sock, sizeof(*sock));

	*socketp = NULL;
}