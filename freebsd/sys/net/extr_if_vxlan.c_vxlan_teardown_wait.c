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
struct vxlan_softc {int vxl_flags; int /*<<< orphan*/  vxl_lock; } ;

/* Variables and functions */
 int VXLAN_FLAG_TEARDOWN ; 
 int /*<<< orphan*/  VXLAN_LOCK_WASSERT (struct vxlan_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  rm_sleep (struct vxlan_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vxlan_teardown_wait(struct vxlan_softc *sc)
{

	VXLAN_LOCK_WASSERT(sc);
	while (sc->vxl_flags & VXLAN_FLAG_TEARDOWN)
		rm_sleep(sc, &sc->vxl_lock, 0, "vxltrn", hz);
}