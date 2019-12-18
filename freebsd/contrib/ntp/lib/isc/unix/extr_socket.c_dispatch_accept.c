#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ev_sender; } ;
typedef  TYPE_1__ isc_socket_newconnev_t ;
typedef  int /*<<< orphan*/  isc_event_t ;
struct TYPE_8__ {TYPE_2__* ev_arg; int /*<<< orphan*/  ev_action; TYPE_2__* ev_sender; } ;
struct TYPE_7__ {int pending_accept; int /*<<< orphan*/  references; TYPE_3__ readable_ev; int /*<<< orphan*/  accept_list; } ;
typedef  TYPE_2__ isc__socket_t ;
typedef  TYPE_3__ intev_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_accept ; 
 int /*<<< orphan*/  isc_task_send (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
dispatch_accept(isc__socket_t *sock) {
	intev_t *iev;
	isc_socket_newconnev_t *ev;

	INSIST(!sock->pending_accept);

	/*
	 * Are there any done events left, or were they all canceled
	 * before the manager got the socket lock?
	 */
	ev = ISC_LIST_HEAD(sock->accept_list);
	if (ev == NULL)
		return;

	sock->pending_accept = 1;
	iev = &sock->readable_ev;

	sock->references++;  /* keep socket around for this internal event */
	iev->ev_sender = sock;
	iev->ev_action = internal_accept;
	iev->ev_arg = sock;

	isc_task_send(ev->ev_sender, (isc_event_t **)&iev);
}