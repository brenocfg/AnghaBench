#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct run_softc {int mac_ver; int mac_rev; } ;
struct TYPE_3__ {int reg; int val; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int nitems (TYPE_1__*) ; 
 TYPE_1__* rt2860_def_bbp ; 
 int run_bbp_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_rt5390_bbp_init (struct run_softc*) ; 

__attribute__((used)) static int
run_bbp_init(struct run_softc *sc)
{
	int i, error, ntries;
	uint8_t bbp0;

	/* wait for BBP to wake up */
	for (ntries = 0; ntries < 20; ntries++) {
		if ((error = run_bbp_read(sc, 0, &bbp0)) != 0)
			return error;
		if (bbp0 != 0 && bbp0 != 0xff)
			break;
	}
	if (ntries == 20)
		return (ETIMEDOUT);

	/* initialize BBP registers to default values */
	if (sc->mac_ver >= 0x5390)
		run_rt5390_bbp_init(sc);
	else {
		for (i = 0; i < nitems(rt2860_def_bbp); i++) {
			run_bbp_write(sc, rt2860_def_bbp[i].reg,
			    rt2860_def_bbp[i].val);
		}
	}

	if (sc->mac_ver == 0x3593) {
		run_bbp_write(sc, 79, 0x13);
		run_bbp_write(sc, 80, 0x05);
		run_bbp_write(sc, 81, 0x33);
		run_bbp_write(sc, 86, 0x46);
		run_bbp_write(sc, 137, 0x0f);
	}
		
	/* fix BBP84 for RT2860E */
	if (sc->mac_ver == 0x2860 && sc->mac_rev != 0x0101)
		run_bbp_write(sc, 84, 0x19);

	if (sc->mac_ver >= 0x3070 && (sc->mac_ver != 0x3593 &&
	    sc->mac_ver != 0x5592)) {
		run_bbp_write(sc, 79, 0x13);
		run_bbp_write(sc, 80, 0x05);
		run_bbp_write(sc, 81, 0x33);
	} else if (sc->mac_ver == 0x2860 && sc->mac_rev == 0x0100) {
		run_bbp_write(sc, 69, 0x16);
		run_bbp_write(sc, 73, 0x12);
	}
	return (0);
}