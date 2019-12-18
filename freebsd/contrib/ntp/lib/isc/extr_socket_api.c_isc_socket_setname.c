#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void isc_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCAPI_SOCKET_VALID (void*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (void*) ; 

void
isc_socket_setname(isc_socket_t *socket, const char *name, void *tag) {
	REQUIRE(ISCAPI_SOCKET_VALID(socket));

	UNUSED(socket);		/* in case REQUIRE() is empty */
	UNUSED(name);
	UNUSED(tag);
}