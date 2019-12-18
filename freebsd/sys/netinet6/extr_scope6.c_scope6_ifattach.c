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
struct scope6_id {int /*<<< orphan*/ * s6id_list; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 size_t IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 size_t IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct scope6_id* malloc (int,int /*<<< orphan*/ ,int) ; 

struct scope6_id *
scope6_ifattach(struct ifnet *ifp)
{
	struct scope6_id *sid;

	sid = malloc(sizeof(*sid), M_IFADDR, M_WAITOK | M_ZERO);
	/*
	 * XXX: IPV6_ADDR_SCOPE_xxx macros are not standard.
	 * Should we rather hardcode here?
	 */
	sid->s6id_list[IPV6_ADDR_SCOPE_INTFACELOCAL] = ifp->if_index;
	sid->s6id_list[IPV6_ADDR_SCOPE_LINKLOCAL] = ifp->if_index;
	return (sid);
}