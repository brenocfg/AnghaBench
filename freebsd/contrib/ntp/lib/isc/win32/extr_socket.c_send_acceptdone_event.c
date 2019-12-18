#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  accept_list; } ;
typedef  TYPE_1__ isc_task_t ;
typedef  TYPE_1__ isc_socket_t ;
struct TYPE_11__ {TYPE_1__* ev_sender; } ;
typedef  TYPE_3__ isc_socket_newconnev_t ;
typedef  int /*<<< orphan*/  isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_LINK_LINKED (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_DEQUEUE (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  isc_task_sendanddetach (TYPE_1__**,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
send_acceptdone_event(isc_socket_t *sock, isc_socket_newconnev_t **adev) {
	isc_task_t *task;

	INSIST(adev != NULL && *adev != NULL);

	task = (*adev)->ev_sender;
	(*adev)->ev_sender = sock;

	if (ISC_LINK_LINKED(*adev, ev_link))
		ISC_LIST_DEQUEUE(sock->accept_list, *adev, ev_link);

	isc_task_sendanddetach(&task, (isc_event_t **)adev);

	CONSISTENT(sock);
}