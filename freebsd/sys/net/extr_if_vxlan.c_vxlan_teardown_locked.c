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
struct vxlan_softc {int vxl_flags; int vxl_vso_mc_index; scalar_t__ vxl_refcnt; int /*<<< orphan*/  vxl_callout; int /*<<< orphan*/  vxl_lock; struct vxlan_socket* vxl_sock; struct ifnet* vxl_ifp; } ;
struct vxlan_socket {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int VXLAN_FLAG_TEARDOWN ; 
 int /*<<< orphan*/  VXLAN_LOCK_WASSERT (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_sleep (struct vxlan_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_free_multicast (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_socket_mc_release_group_by_idx (struct vxlan_socket*,int) ; 
 int /*<<< orphan*/  vxlan_socket_release (struct vxlan_socket*) ; 
 int /*<<< orphan*/  vxlan_socket_remove_softc (struct vxlan_socket*,struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_teardown_complete (struct vxlan_softc*) ; 

__attribute__((used)) static void
vxlan_teardown_locked(struct vxlan_softc *sc)
{
	struct ifnet *ifp;
	struct vxlan_socket *vso;

	ifp = sc->vxl_ifp;

	VXLAN_LOCK_WASSERT(sc);
	MPASS(sc->vxl_flags & VXLAN_FLAG_TEARDOWN);

	ifp->if_flags &= ~IFF_UP;
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	callout_stop(&sc->vxl_callout);
	vso = sc->vxl_sock;
	sc->vxl_sock = NULL;

	VXLAN_WUNLOCK(sc);
	if_link_state_change(ifp, LINK_STATE_DOWN);

	if (vso != NULL) {
		vxlan_socket_remove_softc(vso, sc);

		if (sc->vxl_vso_mc_index != -1) {
			vxlan_socket_mc_release_group_by_idx(vso,
			    sc->vxl_vso_mc_index);
			sc->vxl_vso_mc_index = -1;
		}
	}

	VXLAN_WLOCK(sc);
	while (sc->vxl_refcnt != 0)
		rm_sleep(sc, &sc->vxl_lock, 0, "vxldrn", hz);
	VXLAN_WUNLOCK(sc);

	callout_drain(&sc->vxl_callout);

	vxlan_free_multicast(sc);
	if (vso != NULL)
		vxlan_socket_release(vso);

	vxlan_teardown_complete(sc);
}