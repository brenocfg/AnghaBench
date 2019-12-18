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
struct vxlan_softc {int /*<<< orphan*/  vxl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXLAN_FLAG_INIT ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  wakeup (struct vxlan_softc*) ; 

__attribute__((used)) static void
vxlan_init_complete(struct vxlan_softc *sc)
{

	VXLAN_WLOCK(sc);
	sc->vxl_flags &= ~VXLAN_FLAG_INIT;
	wakeup(sc);
	VXLAN_WUNLOCK(sc);
}