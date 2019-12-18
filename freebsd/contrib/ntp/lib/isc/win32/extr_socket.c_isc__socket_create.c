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
typedef  int /*<<< orphan*/  isc_sockettype_t ;
typedef  int /*<<< orphan*/  isc_socketmgr_t ;
typedef  int /*<<< orphan*/  isc_socket_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  socket_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

isc_result_t
isc__socket_create(isc_socketmgr_t *manager, int pf, isc_sockettype_t type,
		   isc_socket_t **socketp)
{
	return (socket_create(manager, pf, type, socketp, NULL));
}