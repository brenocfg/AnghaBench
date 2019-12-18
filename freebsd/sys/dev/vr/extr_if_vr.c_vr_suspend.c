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
struct vr_softc {int /*<<< orphan*/  vr_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VR_F_SUSPENDED ; 
 int /*<<< orphan*/  VR_LOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_UNLOCK (struct vr_softc*) ; 
 struct vr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr_setwol (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_stop (struct vr_softc*) ; 

__attribute__((used)) static int
vr_suspend(device_t dev)
{
	struct vr_softc		*sc;

	sc = device_get_softc(dev);

	VR_LOCK(sc);
	vr_stop(sc);
	vr_setwol(sc);
	sc->vr_flags |= VR_F_SUSPENDED;
	VR_UNLOCK(sc);

	return (0);
}