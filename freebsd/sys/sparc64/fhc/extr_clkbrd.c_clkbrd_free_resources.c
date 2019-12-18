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
struct clkbrd_softc {int /*<<< orphan*/ ** sc_res; int /*<<< orphan*/ * sc_rid; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CLKBRD_CF ; 
 int CLKBRD_CLKVER ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clkbrd_free_resources(struct clkbrd_softc *sc)
{
	int i;

	for (i = CLKBRD_CF; i <= CLKBRD_CLKVER; i++)
		if (sc->sc_res[i] != NULL)
			bus_release_resource(sc->sc_dev, SYS_RES_MEMORY,
			    sc->sc_rid[i], sc->sc_res[i]);
}