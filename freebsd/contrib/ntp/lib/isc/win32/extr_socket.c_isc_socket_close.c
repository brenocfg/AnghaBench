#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOTIMPLEMENTED ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_SOCKET (TYPE_1__*) ; 
 scalar_t__ isc_sockettype_fdwatch ; 

isc_result_t
isc_socket_close(isc_socket_t *sock) {
	REQUIRE(VALID_SOCKET(sock));
	REQUIRE(sock->type != isc_sockettype_fdwatch);

	return (ISC_R_NOTIMPLEMENTED);
}