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
struct vr_softc {int /*<<< orphan*/  vr_flags; struct ifnet* vr_ifp; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  VR_F_SUSPENDED ; 
 int /*<<< orphan*/  VR_LOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_UNLOCK (struct vr_softc*) ; 
 struct vr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr_clrwol (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_init_locked (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_reset (struct vr_softc*) ; 

__attribute__((used)) static int
vr_resume(device_t dev)
{
	struct vr_softc		*sc;
	struct ifnet		*ifp;

	sc = device_get_softc(dev);

	VR_LOCK(sc);
	ifp = sc->vr_ifp;
	vr_clrwol(sc);
	vr_reset(sc);
	if (ifp->if_flags & IFF_UP)
		vr_init_locked(sc);

	sc->vr_flags &= ~VR_F_SUSPENDED;
	VR_UNLOCK(sc);

	return (0);
}