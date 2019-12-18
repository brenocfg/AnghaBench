#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  size_t u_int ;
struct run_softc {int mac_ver; int mac_rev; int rf24_20mhz; int rf24_40mhz; } ;
struct TYPE_5__ {int reg; int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT3070_OPT_14 ; 
 int RT5390_RESCAL ; 
 size_t nitems (TYPE_1__*) ; 
 TYPE_1__* rt5390_def_rf ; 
 TYPE_1__* rt5392_def_rf ; 
 TYPE_1__* rt5592_def_rf ; 
 int /*<<< orphan*/  run_adjust_freq_offset (struct run_softc*) ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_rt5390_rf_init(struct run_softc *sc)
{
	uint32_t tmp;
	uint8_t rf;
	u_int i;

	/* Toggle RF R2 to initiate calibration. */
	if (sc->mac_ver == 0x5390) {
		run_rt3070_rf_read(sc, 2, &rf);
		run_rt3070_rf_write(sc, 2, rf | RT5390_RESCAL);
		run_delay(sc, 10);
		run_rt3070_rf_write(sc, 2, rf & ~RT5390_RESCAL);
	} else {
		run_rt3070_rf_write(sc, 2, RT5390_RESCAL);
		run_delay(sc, 10);
	}

	/* Initialize RF registers to default value. */
	if (sc->mac_ver == 0x5592) {
		for (i = 0; i < nitems(rt5592_def_rf); i++) {
			run_rt3070_rf_write(sc, rt5592_def_rf[i].reg,
			    rt5592_def_rf[i].val);
		}
		/* Initialize RF frequency offset. */
		run_adjust_freq_offset(sc);
	} else if (sc->mac_ver == 0x5392) {
		for (i = 0; i < nitems(rt5392_def_rf); i++) {
			run_rt3070_rf_write(sc, rt5392_def_rf[i].reg,
			    rt5392_def_rf[i].val);
		}
		if (sc->mac_rev >= 0x0223) {
			run_rt3070_rf_write(sc, 23, 0x0f);
			run_rt3070_rf_write(sc, 24, 0x3e);
			run_rt3070_rf_write(sc, 51, 0x32);
			run_rt3070_rf_write(sc, 53, 0x22);
			run_rt3070_rf_write(sc, 56, 0xc1);
			run_rt3070_rf_write(sc, 59, 0x0f);
		}
	} else {
		for (i = 0; i < nitems(rt5390_def_rf); i++) {
			run_rt3070_rf_write(sc, rt5390_def_rf[i].reg,
			    rt5390_def_rf[i].val);
		}
		if (sc->mac_rev >= 0x0502) {
			run_rt3070_rf_write(sc, 6, 0xe0);
			run_rt3070_rf_write(sc, 25, 0x80);
			run_rt3070_rf_write(sc, 46, 0x73);
			run_rt3070_rf_write(sc, 53, 0x00);
			run_rt3070_rf_write(sc, 56, 0x42);
			run_rt3070_rf_write(sc, 61, 0xd1);
		}
	}

	sc->rf24_20mhz = 0x1f;	/* default value */
	sc->rf24_40mhz = (sc->mac_ver == 0x5592) ? 0 : 0x2f;

	if (sc->mac_rev < 0x0211)
		run_rt3070_rf_write(sc, 27, 0x3);

	run_read(sc, RT3070_OPT_14, &tmp);
	run_write(sc, RT3070_OPT_14, tmp | 1);
}