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
typedef  int /*<<< orphan*/  u_short ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_DYING ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int /*<<< orphan*/  if_ref (struct ifnet*) ; 
 struct ifnet* ifnet_byindex (int /*<<< orphan*/ ) ; 

struct ifnet *
ifnet_byindex_ref(u_short idx)
{
	struct ifnet *ifp;

	NET_EPOCH_ASSERT();

	ifp = ifnet_byindex(idx);
	if (ifp == NULL || (ifp->if_flags & IFF_DYING))
		return (NULL);
	if_ref(ifp);
	return (ifp);
}