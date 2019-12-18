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
struct bwi_regwin {int dummy; } ;
struct bwi_softc {struct bwi_regwin sc_bus_regwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_INTRVEC ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_regwin_enable (struct bwi_softc*,struct bwi_regwin*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_regwin_is_enabled (struct bwi_softc*,struct bwi_regwin*) ; 
 int bwi_regwin_switch (struct bwi_softc*,struct bwi_regwin*,struct bwi_regwin**) ; 

__attribute__((used)) static int
bwi_bus_attach(struct bwi_softc *sc)
{
	struct bwi_regwin *bus, *old;
	int error;

	bus = &sc->sc_bus_regwin;

	error = bwi_regwin_switch(sc, bus, &old);
	if (error)
		return error;

	if (!bwi_regwin_is_enabled(sc, bus))
		bwi_regwin_enable(sc, bus, 0);

	/* Disable interripts */
	CSR_WRITE_4(sc, BWI_INTRVEC, 0);

	return bwi_regwin_switch(sc, old, NULL);
}