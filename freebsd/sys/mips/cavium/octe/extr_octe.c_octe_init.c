#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_drv_flags; int if_flags; } ;
struct TYPE_3__ {int if_flags; int /*<<< orphan*/ * miibus; int /*<<< orphan*/  (* open ) (struct ifnet*) ;struct ifnet* ifp; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  cvm_oct_common_poll (struct ifnet*) ; 
 int /*<<< orphan*/  cvm_oct_common_set_mac_address (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_common_set_multicast_list (struct ifnet*) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octe_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

__attribute__((used)) static void
octe_init(void *arg)
{
	struct ifnet *ifp;
	cvm_oct_private_t *priv;

	priv = arg;
	ifp = priv->ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		octe_stop(priv);

	if (priv->open != NULL)
		priv->open(ifp);

	if (((ifp->if_flags ^ priv->if_flags) & (IFF_ALLMULTI | IFF_MULTICAST | IFF_PROMISC)) != 0)
		cvm_oct_common_set_multicast_list(ifp);

	cvm_oct_common_set_mac_address(ifp, IF_LLADDR(ifp));

	cvm_oct_common_poll(ifp);

	if (priv->miibus != NULL)
		mii_mediachg(device_get_softc(priv->miibus));

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}