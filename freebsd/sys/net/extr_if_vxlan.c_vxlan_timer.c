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
struct vxlan_softc {int /*<<< orphan*/  vxl_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXLAN_LOCK_WASSERT (struct vxlan_softc*) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  vxlan_ftable_expire (struct vxlan_softc*) ; 
 int vxlan_ftable_prune_period ; 

__attribute__((used)) static void
vxlan_timer(void *xsc)
{
	struct vxlan_softc *sc;

	sc = xsc;
	VXLAN_LOCK_WASSERT(sc);

	vxlan_ftable_expire(sc);
	callout_schedule(&sc->vxl_callout, vxlan_ftable_prune_period * hz);
}