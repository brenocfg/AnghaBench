#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_1__ in; } ;
struct TYPE_7__ {int family; TYPE_2__ type; } ;
typedef  TYPE_3__ isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_IPADDR_ISEXPERIMENTAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_TF (int /*<<< orphan*/ ) ; 

isc_boolean_t
isc_netaddr_isexperimental(isc_netaddr_t *na) {
	switch (na->family) {
	case AF_INET:
		return (ISC_TF(ISC_IPADDR_ISEXPERIMENTAL(na->type.in.s_addr)));
	default:
		return (ISC_FALSE);  /* XXXMLG ? */
	}
}