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
struct vi_info {struct ifnet* ifp; int /*<<< orphan*/  tick; } ;
struct ifnet {int if_capabilities; } ;

/* Variables and functions */
 int IFCAP_NETMAP ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbe_nm_detach (struct vi_info*) ; 
 int /*<<< orphan*/  cxgbe_uninit_synchronized (struct vi_info*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  vi_full_uninit (struct vi_info*) ; 

__attribute__((used)) static void
cxgbe_vi_detach(struct vi_info *vi)
{
	struct ifnet *ifp = vi->ifp;

	ether_ifdetach(ifp);

	/* Let detach proceed even if these fail. */
#ifdef DEV_NETMAP
	if (ifp->if_capabilities & IFCAP_NETMAP)
		cxgbe_nm_detach(vi);
#endif
	cxgbe_uninit_synchronized(vi);
	callout_drain(&vi->tick);
	vi_full_uninit(vi);

	if_free(vi->ifp);
	vi->ifp = NULL;
}