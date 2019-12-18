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
 int /*<<< orphan*/  vtblk_startio (struct vtblk_softc*) ; 

__attribute__((used)) static int
vtblk_resume(device_t dev)
{
	struct vtblk_softc *sc;

	sc = device_get_softc(dev);

	VTBLK_LOCK(sc);
	/* XXX BMV: virtio_reinit(), etc needed here? */
	sc->vtblk_flags &= ~VTBLK_FLAG_SUSPEND;
	vtblk_startio(sc);
	VTBLK_UNLOCK(sc);

	return (0);
}