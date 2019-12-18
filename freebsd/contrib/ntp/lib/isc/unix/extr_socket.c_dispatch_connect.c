#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ev_sender; } ;
typedef  TYPE_1__ isc_socket_connev_t ;
typedef  int /*<<< orphan*/  isc_event_t ;
struct TYPE_7__ {TYPE_2__* ev_arg; int /*<<< orphan*/  ev_action; TYPE_2__* ev_sender; } ;
struct TYPE_6__ {int /*<<< orphan*/  references; int /*<<< orphan*/  connecting; TYPE_1__* connect_ev; TYPE_3__ writable_ev; } ;
typedef  TYPE_2__ isc__socket_t ;
typedef  TYPE_3__ intev_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_connect ; 
 int /*<<< orphan*/  isc_task_send (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
dispatch_connect(isc__socket_t *sock) {
	intev_t *iev;
	isc_socket_connev_t *ev;

	iev = &sock->writable_ev;

	ev = sock->connect_ev;
	INSIST(ev != NULL); /* XXX */

	INSIST(sock->connecting);

	sock->references++;  /* keep socket around for this internal event */
	iev->ev_sender = sock;
	iev->ev_action = internal_connect;
	iev->ev_arg = sock;

	isc_task_send(ev->ev_sender, (isc_event_t **)&iev);
}