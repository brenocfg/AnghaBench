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
struct vtnet_softc {int /*<<< orphan*/  vtnet_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_CORE_LOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_UNLOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_FLAG_SUSPENDED ; 
 struct vtnet_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_stop (struct vtnet_softc*) ; 

__attribute__((used)) static int
vtnet_suspend(device_t dev)
{
	struct vtnet_softc *sc;

	sc = device_get_softc(dev);

	VTNET_CORE_LOCK(sc);
	vtnet_stop(sc);
	sc->vtnet_flags |= VTNET_FLAG_SUSPENDED;
	VTNET_CORE_UNLOCK(sc);

	return (0);
}