#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fd; TYPE_1__* manager; } ;
typedef  TYPE_2__ isc_socket_t ;
struct TYPE_5__ {int /*<<< orphan*/  totalSockets; } ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_CLOSED ; 
 int /*<<< orphan*/  _set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 

void
socket_close(isc_socket_t *sock) {

	REQUIRE(sock != NULL);

	if (sock->fd != INVALID_SOCKET) {
		closesocket(sock->fd);
		sock->fd = INVALID_SOCKET;
		_set_state(sock, SOCK_CLOSED);
		InterlockedDecrement(&sock->manager->totalSockets);
	}
}