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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_MULTI_LOCK () ; 
 int /*<<< orphan*/  IN_MULTI_UNLOCK () ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 int /*<<< orphan*/  V_udbinfo ; 
 int /*<<< orphan*/  V_ulitecbinfo ; 
 int /*<<< orphan*/  in_pcbpurgeif0 (int /*<<< orphan*/ *,struct ifnet*) ; 
 int /*<<< orphan*/  in_purgemaddrs (struct ifnet*) ; 

void
in_ifdetach(struct ifnet *ifp)
{
	IN_MULTI_LOCK();
	in_pcbpurgeif0(&V_ripcbinfo, ifp);
	in_pcbpurgeif0(&V_udbinfo, ifp);
	in_pcbpurgeif0(&V_ulitecbinfo, ifp);
	in_purgemaddrs(ifp);
	IN_MULTI_UNLOCK();
}