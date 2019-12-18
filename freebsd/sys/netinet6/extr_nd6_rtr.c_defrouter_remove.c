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
 int /*<<< orphan*/  ND6_WLOCK () ; 
 int /*<<< orphan*/  ND6_WUNLOCK () ; 
 int /*<<< orphan*/  defrouter_del (struct nd_defrouter*) ; 
 struct nd_defrouter* defrouter_lookup_locked (struct in6_addr*,struct ifnet*) ; 
 int /*<<< orphan*/  defrouter_rele (struct nd_defrouter*) ; 
 int /*<<< orphan*/  defrouter_unlink (struct nd_defrouter*,int /*<<< orphan*/ *) ; 

bool
defrouter_remove(struct in6_addr *addr, struct ifnet *ifp)
{
	struct nd_defrouter *dr;

	ND6_WLOCK();
	dr = defrouter_lookup_locked(addr, ifp);
	if (dr == NULL) {
		ND6_WUNLOCK();
		return (false);
	}

	defrouter_unlink(dr, NULL);
	ND6_WUNLOCK();
	defrouter_del(dr);
	defrouter_rele(dr);
	return (true);
}