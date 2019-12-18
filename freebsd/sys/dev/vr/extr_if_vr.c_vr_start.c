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
struct vr_softc {int dummy; } ;
struct ifnet {struct vr_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VR_LOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_UNLOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
vr_start(struct ifnet *ifp)
{
	struct vr_softc		*sc;

	sc = ifp->if_softc;
	VR_LOCK(sc);
	vr_start_locked(ifp);
	VR_UNLOCK(sc);
}