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
struct ifnet {int if_drv_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct ifnet*) ;struct ifnet* ifp; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

__attribute__((used)) static void
octe_stop(void *arg)
{
	struct ifnet *ifp;
	cvm_oct_private_t *priv;

	priv = arg;
	ifp = priv->ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	if (priv->stop != NULL)
		priv->stop(ifp);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
}