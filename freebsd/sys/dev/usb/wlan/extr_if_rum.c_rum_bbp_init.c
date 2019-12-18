#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct rum_softc {TYPE_1__* bbp_prom; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_5__ {int reg; int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int nitems (TYPE_2__*) ; 
 int rum_bbp_read (struct rum_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_bbp_write (struct rum_softc*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* rum_def_bbp ; 
 scalar_t__ rum_pause (struct rum_softc*,int) ; 

__attribute__((used)) static int
rum_bbp_init(struct rum_softc *sc)
{
	int i, ntries;

	/* wait for BBP to be ready */
	for (ntries = 0; ntries < 100; ntries++) {
		const uint8_t val = rum_bbp_read(sc, 0);
		if (val != 0 && val != 0xff)
			break;
		if (rum_pause(sc, hz / 100))
			break;
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "timeout waiting for BBP\n");
		return EIO;
	}

	/* initialize BBP registers to default values */
	for (i = 0; i < nitems(rum_def_bbp); i++)
		rum_bbp_write(sc, rum_def_bbp[i].reg, rum_def_bbp[i].val);

	/* write vendor-specific BBP values (from EEPROM) */
	for (i = 0; i < 16; i++) {
		if (sc->bbp_prom[i].reg == 0 || sc->bbp_prom[i].reg == 0xff)
			continue;
		rum_bbp_write(sc, sc->bbp_prom[i].reg, sc->bbp_prom[i].val);
	}

	return 0;
}