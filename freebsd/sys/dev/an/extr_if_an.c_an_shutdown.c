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
struct an_softc {int an_gone; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int /*<<< orphan*/  an_stop (struct an_softc*) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
an_shutdown(device_t dev)
{
	struct an_softc		*sc;

	sc = device_get_softc(dev);
	AN_LOCK(sc);
	an_stop(sc);
	sc->an_gone = 1;
	AN_UNLOCK(sc);

	return (0);
}