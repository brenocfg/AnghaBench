#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  in6; } ;
struct TYPE_5__ {int family; TYPE_1__ type; } ;
typedef  TYPE_2__ isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TF (int /*<<< orphan*/ ) ; 

isc_boolean_t
isc_netaddr_islinklocal(isc_netaddr_t *na) {
	switch (na->family) {
	case AF_INET:
		return (ISC_FALSE);
	case AF_INET6:
		return (ISC_TF(IN6_IS_ADDR_LINKLOCAL(&na->type.in6)));
	default:
		return (ISC_FALSE);
	}
}