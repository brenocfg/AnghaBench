#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ isc_socketevent_t ;
struct TYPE_8__ {int /*<<< orphan*/  recv_list; } ;
typedef  TYPE_2__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_recvdone_event (TYPE_2__*,TYPE_1__**) ; 

__attribute__((used)) static void
send_recvdone_abort(isc_socket_t *sock, isc_result_t result) {
	isc_socketevent_t *dev;

	while (!ISC_LIST_EMPTY(sock->recv_list)) {
		dev = ISC_LIST_HEAD(sock->recv_list);
		dev->result = result;
		send_recvdone_event(sock, &dev);
	}
}