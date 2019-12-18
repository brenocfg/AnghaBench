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
struct rt2860_softc {int nrxchains; int mac_ver; } ;
struct TYPE_3__ {int reg; int val; } ;

/* Variables and functions */
 int RT5390_MAC_IF_CTRL ; 
 int RT5390_MLD ; 
 int nitems (TYPE_1__*) ; 
 int rt2860_mcu_bbp_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt2860_mcu_bbp_write (struct rt2860_softc*,int,int) ; 
 TYPE_1__* rt5390_def_bbp ; 

__attribute__((used)) static void
rt5390_bbp_init(struct rt2860_softc *sc)
{
	uint8_t bbp;
	int i;

	/* Apply maximum likelihood detection for 2 stream case. */
	if (sc->nrxchains > 1) {
		bbp = rt2860_mcu_bbp_read(sc, 105);
		rt2860_mcu_bbp_write(sc, 105, bbp | RT5390_MLD);
	}

	/* Avoid data lost and CRC error. */
	bbp = rt2860_mcu_bbp_read(sc, 4);
	rt2860_mcu_bbp_write(sc, 4, bbp | RT5390_MAC_IF_CTRL);

	for (i = 0; i < nitems(rt5390_def_bbp); i++) {
		rt2860_mcu_bbp_write(sc, rt5390_def_bbp[i].reg,
		    rt5390_def_bbp[i].val);
	}

	if (sc->mac_ver == 0x5392) {
		rt2860_mcu_bbp_write(sc, 84, 0x9a);
		rt2860_mcu_bbp_write(sc, 95, 0x9a);
		rt2860_mcu_bbp_write(sc, 98, 0x12);
		rt2860_mcu_bbp_write(sc, 106, 0x05);
		rt2860_mcu_bbp_write(sc, 134, 0xd0);
		rt2860_mcu_bbp_write(sc, 135, 0xf6);
	}

	bbp = rt2860_mcu_bbp_read(sc, 152);
	rt2860_mcu_bbp_write(sc, 152, bbp | 0x80);

	/* Disable hardware antenna diversity. */
	if (sc->mac_ver == 0x5390)
		rt2860_mcu_bbp_write(sc, 154, 0);
}