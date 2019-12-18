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
struct vxlan_softc {int /*<<< orphan*/  vxl_lock; int /*<<< orphan*/  vxl_media; } ;
struct ifnet {struct vxlan_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VXLAN ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct vxlan_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_ftable_fini (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_ftable_flush (struct vxlan_softc*,int) ; 
 int /*<<< orphan*/  vxlan_sysctl_destroy (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_teardown (struct vxlan_softc*) ; 

__attribute__((used)) static void
vxlan_clone_destroy(struct ifnet *ifp)
{
	struct vxlan_softc *sc;

	sc = ifp->if_softc;

	vxlan_teardown(sc);

	vxlan_ftable_flush(sc, 1);

	ether_ifdetach(ifp);
	if_free(ifp);
	ifmedia_removeall(&sc->vxl_media);

	vxlan_ftable_fini(sc);

	vxlan_sysctl_destroy(sc);
	rm_destroy(&sc->vxl_lock);
	free(sc, M_VXLAN);
}