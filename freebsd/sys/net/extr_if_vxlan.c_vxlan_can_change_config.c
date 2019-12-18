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
struct vxlan_softc {int vxl_flags; struct ifnet* vxl_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int VXLAN_FLAG_INIT ; 
 int VXLAN_FLAG_TEARDOWN ; 
 int /*<<< orphan*/  VXLAN_LOCK_ASSERT (struct vxlan_softc*) ; 

__attribute__((used)) static int
vxlan_can_change_config(struct vxlan_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->vxl_ifp;
	VXLAN_LOCK_ASSERT(sc);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return (0);
	if (sc->vxl_flags & (VXLAN_FLAG_INIT | VXLAN_FLAG_TEARDOWN))
		return (0);

	return (1);
}