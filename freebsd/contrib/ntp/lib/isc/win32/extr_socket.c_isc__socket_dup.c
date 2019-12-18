#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  pf; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOTIMPLEMENTED ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_SOCKET (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,TYPE_1__*) ; 

isc_result_t
isc__socket_dup(isc_socket_t *sock, isc_socket_t **socketp) {
	REQUIRE(VALID_SOCKET(sock));
	REQUIRE(socketp != NULL && *socketp == NULL);

#if 1
	return (ISC_R_NOTIMPLEMENTED);
#else
	return (socket_create(sock->manager, sock->pf, sock->type,
			      socketp, sock));
#endif
}