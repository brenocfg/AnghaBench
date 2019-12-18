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
struct ec_softc {scalar_t__ have_arbitrator; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_release (struct ec_softc*) ; 
 struct ec_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ec_detach(device_t dev)
{
	struct ec_softc *sc;

	sc = device_get_softc(dev);

	if (sc->have_arbitrator) {
		bus_release(sc);
	}

	return (0);
}