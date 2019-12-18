#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* fdwatchpoke ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCAPI_SOCKET_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

isc_result_t
isc_socket_fdwatchpoke(isc_socket_t *sock, int flags)
{
	REQUIRE(ISCAPI_SOCKET_VALID(sock));

	return(sock->methods->fdwatchpoke(sock, flags));
}