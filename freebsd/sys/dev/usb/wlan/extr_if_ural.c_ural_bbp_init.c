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
struct ural_softc {TYPE_1__* bbp_prom; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_5__ {int reg; int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RAL_BBP_VERSION ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int nitems (TYPE_2__*) ; 
 scalar_t__ ural_bbp_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_bbp_write (struct ural_softc*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* ural_def_bbp ; 
 scalar_t__ ural_pause (struct ural_softc*,int) ; 

__attribute__((used)) static int
ural_bbp_init(struct ural_softc *sc)
{
	int i, ntries;

	/* wait for BBP to be ready */
	for (ntries = 0; ntries < 100; ntries++) {
		if (ural_bbp_read(sc, RAL_BBP_VERSION) != 0)
			break;
		if (ural_pause(sc, hz / 100))
			break;
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "timeout waiting for BBP\n");
		return EIO;
	}

	/* initialize BBP registers to default values */
	for (i = 0; i < nitems(ural_def_bbp); i++)
		ural_bbp_write(sc, ural_def_bbp[i].reg, ural_def_bbp[i].val);

#if 0
	/* initialize BBP registers to values stored in EEPROM */
	for (i = 0; i < 16; i++) {
		if (sc->bbp_prom[i].reg == 0xff)
			continue;
		ural_bbp_write(sc, sc->bbp_prom[i].reg, sc->bbp_prom[i].val);
	}
#endif

	return 0;
}