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
struct vge_softc {int dummy; } ;
struct ifnet {struct vge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGE_LOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_UNLOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
vge_start(struct ifnet *ifp)
{
	struct vge_softc *sc;

	sc = ifp->if_softc;
	VGE_LOCK(sc);
	vge_start_locked(ifp);
	VGE_UNLOCK(sc);
}