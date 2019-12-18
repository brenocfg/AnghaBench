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
typedef  int /*<<< orphan*/  uint32_t ;
struct ifnet {int /*<<< orphan*/  if_index; } ;
struct TYPE_2__ {int /*<<< orphan*/ * s6id_list; } ;

/* Variables and functions */
 int IPV6_ADDR_SCOPES_COUNT ; 
 int IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 int IPV6_ADDR_SCOPE_LINKLOCAL ; 
 TYPE_1__* SID (struct ifnet const*) ; 

uint32_t
in6_getscopezone(const struct ifnet *ifp, int scope)
{

	if (scope == IPV6_ADDR_SCOPE_INTFACELOCAL ||
	    scope == IPV6_ADDR_SCOPE_LINKLOCAL)
		return (ifp->if_index);
	if (scope >= 0 && scope < IPV6_ADDR_SCOPES_COUNT)
		return (SID(ifp)->s6id_list[scope]);
	return (0);
}