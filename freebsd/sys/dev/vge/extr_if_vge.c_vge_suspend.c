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
struct vge_softc {int /*<<< orphan*/  vge_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VGE_FLAG_SUSPENDED ; 
 int /*<<< orphan*/  VGE_LOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_UNLOCK (struct vge_softc*) ; 
 struct vge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_setwol (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_stop (struct vge_softc*) ; 

__attribute__((used)) static int
vge_suspend(device_t dev)
{
	struct vge_softc *sc;

	sc = device_get_softc(dev);

	VGE_LOCK(sc);
	vge_stop(sc);
	vge_setwol(sc);
	sc->vge_flags |= VGE_FLAG_SUSPENDED;
	VGE_UNLOCK(sc);

	return (0);
}