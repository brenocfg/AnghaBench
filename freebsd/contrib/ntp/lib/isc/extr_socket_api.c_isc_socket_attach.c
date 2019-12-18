#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_socket_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* attach ) (TYPE_2__*,TYPE_2__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int) ; 
 int ISCAPI_SOCKET_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_2__**) ; 

void
isc_socket_attach(isc_socket_t *sock, isc_socket_t **socketp) {
	REQUIRE(ISCAPI_SOCKET_VALID(sock));
	REQUIRE(socketp != NULL && *socketp == NULL);

	sock->methods->attach(sock, socketp);

	ENSURE(*socketp == sock);
}