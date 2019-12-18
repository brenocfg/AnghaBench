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
struct stge_softc {int sc_suspended; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stge_setwol (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_stop (struct stge_softc*) ; 

__attribute__((used)) static int
stge_suspend(device_t dev)
{
	struct stge_softc *sc;

	sc = device_get_softc(dev);

	STGE_LOCK(sc);
	stge_stop(sc);
	sc->sc_suspended = 1;
	stge_setwol(sc);
	STGE_UNLOCK(sc);

	return (0);
}