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
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_softc; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  ng_eiface_start2 ; 
 scalar_t__ ng_send_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_eiface_start(struct ifnet *ifp)
{
	const priv_p priv = (priv_p)ifp->if_softc;

	/* Don't do anything if output is active */
	if (ifp->if_drv_flags & IFF_DRV_OACTIVE)
		return;

	ifp->if_drv_flags |= IFF_DRV_OACTIVE;

	if (ng_send_fn(priv->node, NULL, &ng_eiface_start2, ifp, 0) != 0)
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}