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
struct ifnet {int /*<<< orphan*/  if_epoch_ctx; int /*<<< orphan*/  if_refcount; int /*<<< orphan*/  if_index; int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_vnet; int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DYING ; 
 int /*<<< orphan*/  IFNET_WLOCK () ; 
 int /*<<< orphan*/  IFNET_WUNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_destroy ; 
 int /*<<< orphan*/  ifindex_free_locked (int /*<<< orphan*/ ) ; 
 struct ifnet* ifnet_byindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_epoch_preempt ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
if_free(struct ifnet *ifp)
{

	ifp->if_flags |= IFF_DYING;			/* XXX: Locking */

	CURVNET_SET_QUIET(ifp->if_vnet);
	IFNET_WLOCK();
	KASSERT(ifp == ifnet_byindex(ifp->if_index),
	    ("%s: freeing unallocated ifnet", ifp->if_xname));

	ifindex_free_locked(ifp->if_index);
	IFNET_WUNLOCK();

	if (refcount_release(&ifp->if_refcount))
		epoch_call(net_epoch_preempt, &ifp->if_epoch_ctx, if_destroy);
	CURVNET_RESTORE();
}