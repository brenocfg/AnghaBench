#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * connect_ev; } ;
typedef  TYPE_1__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_socket_connev_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 

__attribute__((used)) static isc_boolean_t
connectdone_is_active(isc_socket_t *sock, isc_socket_connev_t *dev)
{
	return (sock->connect_ev == dev ? ISC_TRUE : ISC_FALSE);
}