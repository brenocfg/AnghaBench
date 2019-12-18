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
struct TYPE_3__ {int /*<<< orphan*/  accept_list; } ;
typedef  TYPE_1__ isc_socket_t ;
typedef  int /*<<< orphan*/  isc_socket_newconnev_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/ * ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ISC_LIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  ev_link ; 

__attribute__((used)) static isc_boolean_t
acceptdone_is_active(isc_socket_t *sock, isc_socket_newconnev_t *dev)
{
	isc_socket_newconnev_t *ldev;

	ldev = ISC_LIST_HEAD(sock->accept_list);
	while (ldev != NULL && ldev != dev)
		ldev = ISC_LIST_NEXT(ldev, ev_link);

	return (ldev == NULL ? ISC_FALSE : ISC_TRUE);
}