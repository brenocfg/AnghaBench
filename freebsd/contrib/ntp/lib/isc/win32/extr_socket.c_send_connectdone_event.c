#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * connect_ev; } ;
typedef  TYPE_1__ isc_task_t ;
typedef  TYPE_1__ isc_socket_t ;
struct TYPE_9__ {TYPE_1__* ev_sender; } ;
typedef  TYPE_3__ isc_socket_connev_t ;
typedef  int /*<<< orphan*/  isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  isc_task_sendanddetach (TYPE_1__**,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
send_connectdone_event(isc_socket_t *sock, isc_socket_connev_t **cdev) {
	isc_task_t *task;

	INSIST(cdev != NULL && *cdev != NULL);

	task = (*cdev)->ev_sender;
	(*cdev)->ev_sender = sock;

	sock->connect_ev = NULL;

	isc_task_sendanddetach(&task, (isc_event_t **)cdev);

	CONSISTENT(sock);
}