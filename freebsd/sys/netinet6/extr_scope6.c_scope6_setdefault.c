#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifnet {scalar_t__ if_index; } ;
struct TYPE_2__ {scalar_t__* s6id_list; } ;

/* Variables and functions */
 size_t IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 size_t IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int /*<<< orphan*/  SCOPE6_LOCK () ; 
 int /*<<< orphan*/  SCOPE6_UNLOCK () ; 
 TYPE_1__ V_sid_default ; 

void
scope6_setdefault(struct ifnet *ifp)
{

	/*
	 * Currently, this function just sets the default "interfaces"
	 * and "links" according to the given interface.
	 * We might eventually have to separate the notion of "link" from
	 * "interface" and provide a user interface to set the default.
	 */
	SCOPE6_LOCK();
	if (ifp) {
		V_sid_default.s6id_list[IPV6_ADDR_SCOPE_INTFACELOCAL] =
			ifp->if_index;
		V_sid_default.s6id_list[IPV6_ADDR_SCOPE_LINKLOCAL] =
			ifp->if_index;
	} else {
		V_sid_default.s6id_list[IPV6_ADDR_SCOPE_INTFACELOCAL] = 0;
		V_sid_default.s6id_list[IPV6_ADDR_SCOPE_LINKLOCAL] = 0;
	}
	SCOPE6_UNLOCK();
}