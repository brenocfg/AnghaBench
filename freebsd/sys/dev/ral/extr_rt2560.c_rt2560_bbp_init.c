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
struct rt2560_softc {TYPE_1__* bbp_prom; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_5__ {int reg; int val; } ;
struct TYPE_4__ {scalar_t__ reg; scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  RT2560_BBP_VERSION ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nitems (TYPE_2__*) ; 
 scalar_t__ rt2560_bbp_read (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_bbp_write (struct rt2560_softc*,int,int) ; 
 TYPE_2__* rt2560_def_bbp ; 

__attribute__((used)) static int
rt2560_bbp_init(struct rt2560_softc *sc)
{
	int i, ntries;

	/* wait for BBP to be ready */
	for (ntries = 0; ntries < 100; ntries++) {
		if (rt2560_bbp_read(sc, RT2560_BBP_VERSION) != 0)
			break;
		DELAY(1);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "timeout waiting for BBP\n");
		return EIO;
	}

	/* initialize BBP registers to default values */
	for (i = 0; i < nitems(rt2560_def_bbp); i++) {
		rt2560_bbp_write(sc, rt2560_def_bbp[i].reg,
		    rt2560_def_bbp[i].val);
	}

	/* initialize BBP registers to values stored in EEPROM */
	for (i = 0; i < 16; i++) {
		if (sc->bbp_prom[i].reg == 0 && sc->bbp_prom[i].val == 0)
			break;
		rt2560_bbp_write(sc, sc->bbp_prom[i].reg, sc->bbp_prom[i].val);
	}
	rt2560_bbp_write(sc, 17, 0x48);	/* XXX restore bbp17 */

	return 0;
}