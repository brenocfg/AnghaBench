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
struct vtblk_softc {int /*<<< orphan*/  vtblk_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTBLK_FLAG_SUSPEND ; 
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 struct vtblk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int vtblk_quiesce (struct vtblk_softc*) ; 

__attribute__((used)) static int
vtblk_suspend(device_t dev)
{
	struct vtblk_softc *sc;
	int error;

	sc = device_get_softc(dev);

	VTBLK_LOCK(sc);
	sc->vtblk_flags |= VTBLK_FLAG_SUSPEND;
	/* XXX BMV: virtio_stop(), etc needed here? */
	error = vtblk_quiesce(sc);
	if (error)
		sc->vtblk_flags &= ~VTBLK_FLAG_SUSPEND;
	VTBLK_UNLOCK(sc);

	return (error);
}