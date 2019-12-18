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
struct rtentry {int rt_flags; struct ifnet* rt_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int RTF_UP ; 

__attribute__((used)) static int
rt_ifdelroute(const struct rtentry *rt, void *arg)
{
	struct ifnet	*ifp = arg;

	if (rt->rt_ifp != ifp)
		return (0);

	/*
	 * Protect (sorta) against walktree recursion problems
	 * with cloned routes
	 */
	if ((rt->rt_flags & RTF_UP) == 0)
		return (0);

	return (1);
}