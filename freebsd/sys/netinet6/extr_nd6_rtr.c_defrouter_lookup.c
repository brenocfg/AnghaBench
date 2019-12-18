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
struct nd_defrouter {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND6_RLOCK () ; 
 int /*<<< orphan*/  ND6_RUNLOCK () ; 
 struct nd_defrouter* defrouter_lookup_locked (struct in6_addr*,struct ifnet*) ; 

struct nd_defrouter *
defrouter_lookup(struct in6_addr *addr, struct ifnet *ifp)
{
	struct nd_defrouter *dr;

	ND6_RLOCK();
	dr = defrouter_lookup_locked(addr, ifp);
	ND6_RUNLOCK();
	return (dr);
}