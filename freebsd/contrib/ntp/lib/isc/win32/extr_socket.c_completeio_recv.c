#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ n; scalar_t__ minimum; int /*<<< orphan*/  result; } ;
typedef  TYPE_2__ isc_socketevent_t ;
struct TYPE_10__ {scalar_t__ remaining; } ;
struct TYPE_12__ {scalar_t__ pending_recv; int /*<<< orphan*/  recv_list; TYPE_1__ recvbuf; } ;
typedef  TYPE_3__ isc_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 TYPE_2__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  fill_recv (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  send_recvdone_event (TYPE_3__*,TYPE_2__**) ; 

__attribute__((used)) static void
completeio_recv(isc_socket_t *sock)
{
	isc_socketevent_t *dev;

	/*
	 * If we are in the process of filling our buffer, we cannot
	 * touch it yet, so don't.
	 */
	if (sock->pending_recv > 0)
		return;

	while (sock->recvbuf.remaining > 0 && !ISC_LIST_EMPTY(sock->recv_list)) {
		dev = ISC_LIST_HEAD(sock->recv_list);

		/*
		 * See if we have sufficient data in our receive buffer
		 * to handle this.  If we do, copy out the data.
		 */
		fill_recv(sock, dev);

		/*
		 * Did we satisfy it?
		 */
		if (dev->n >= dev->minimum) {
			dev->result = ISC_R_SUCCESS;
			send_recvdone_event(sock, &dev);
		}
	}
}