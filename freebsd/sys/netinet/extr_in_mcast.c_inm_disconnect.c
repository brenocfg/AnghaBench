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
struct in_multi {struct ifmultiaddr* inm_ifma; struct ifnet* inm_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_multiaddrs; } ;
struct ifmultiaddr {int ifma_flags; scalar_t__ ifma_refcount; struct ifnet* ifma_ifp; struct ifmultiaddr* ifma_llifma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_STAILQ_REMOVE (int /*<<< orphan*/ *,struct ifmultiaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFMA_F_ENQUEUED ; 
 int /*<<< orphan*/  IF_ADDR_WLOCK_ASSERT (struct ifnet*) ; 
 int /*<<< orphan*/  MCDPRINTF (char*,struct ifmultiaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  if_freemulti (struct ifmultiaddr*) ; 
 int /*<<< orphan*/  if_ref (struct ifnet*) ; 
 int /*<<< orphan*/  ifma_link ; 
 int ifma_restart ; 
 int /*<<< orphan*/  ifmultiaddr ; 

void
inm_disconnect(struct in_multi *inm)
{
	struct ifnet *ifp;
	struct ifmultiaddr *ifma, *ll_ifma;

	ifp = inm->inm_ifp;
	IF_ADDR_WLOCK_ASSERT(ifp);
	ifma = inm->inm_ifma;

	if_ref(ifp);
	if (ifma->ifma_flags & IFMA_F_ENQUEUED) {
		CK_STAILQ_REMOVE(&ifp->if_multiaddrs, ifma, ifmultiaddr, ifma_link);
		ifma->ifma_flags &= ~IFMA_F_ENQUEUED;
	}
	MCDPRINTF("removed ifma: %p from %s\n", ifma, ifp->if_xname);
	if ((ll_ifma = ifma->ifma_llifma) != NULL) {
		MPASS(ifma != ll_ifma);
		ifma->ifma_llifma = NULL;
		MPASS(ll_ifma->ifma_llifma == NULL);
		MPASS(ll_ifma->ifma_ifp == ifp);
		if (--ll_ifma->ifma_refcount == 0) {
			if (ll_ifma->ifma_flags & IFMA_F_ENQUEUED) {
				CK_STAILQ_REMOVE(&ifp->if_multiaddrs, ll_ifma, ifmultiaddr, ifma_link);
				ll_ifma->ifma_flags &= ~IFMA_F_ENQUEUED;
			}
			MCDPRINTF("removed ll_ifma: %p from %s\n", ll_ifma, ifp->if_xname);
			if_freemulti(ll_ifma);
			ifma_restart = true;
		}
	}
}