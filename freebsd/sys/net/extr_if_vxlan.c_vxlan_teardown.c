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
struct vxlan_softc {int vxl_flags; } ;

/* Variables and functions */
 int VXLAN_FLAG_TEARDOWN ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_teardown_locked (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_teardown_wait (struct vxlan_softc*) ; 

__attribute__((used)) static void
vxlan_teardown(struct vxlan_softc *sc)
{

	VXLAN_WLOCK(sc);
	if (sc->vxl_flags & VXLAN_FLAG_TEARDOWN) {
		vxlan_teardown_wait(sc);
		VXLAN_WUNLOCK(sc);
		return;
	}

	sc->vxl_flags |= VXLAN_FLAG_TEARDOWN;
	vxlan_teardown_locked(sc);
}