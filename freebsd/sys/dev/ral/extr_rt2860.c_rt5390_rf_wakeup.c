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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct rt2860_softc {int mac_ver; int mac_rev; scalar_t__ patch_dac; } ;

/* Variables and functions */
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT3070_LDO_CFG0 ; 
 int RT3070_PLL_PD ; 
 int RT3070_RF_BLOCK ; 
 int RT3070_RX0_PD ; 
 int RT3070_RX1_PD ; 
 int RT3070_TX0_PD ; 
 int RT3070_TX1_PD ; 
 int RT3593_RESCAL ; 
 int RT3593_VCOCAL ; 
 int RT3593_VCO_IC ; 
 int RT5390_RX_CTB ; 
 int rt3090_rf_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt3090_rf_write (struct rt2860_softc*,int,int) ; 

__attribute__((used)) static void
rt5390_rf_wakeup(struct rt2860_softc *sc)
{
	uint32_t tmp;
	uint8_t rf;

	rf = rt3090_rf_read(sc, 1);
	rf |= RT3070_RF_BLOCK | RT3070_PLL_PD | RT3070_RX0_PD | 
	    RT3070_TX0_PD;
	if (sc->mac_ver == 0x5392)
		rf |= RT3070_RX1_PD | RT3070_TX1_PD;
	rt3090_rf_write(sc, 1, rf);

	rf = rt3090_rf_read(sc, 6);
	rf |= RT3593_VCO_IC | RT3593_VCOCAL;
	if (sc->mac_ver == 0x5390)
		rf &= ~RT3593_VCO_IC;
	rt3090_rf_write(sc, 6, rf);

	rt3090_rf_write(sc, 2, rt3090_rf_read(sc, 2) | RT3593_RESCAL);

	rf = rt3090_rf_read(sc, 22);
	rf = (rf & ~0xe0) | 0x20;
	rt3090_rf_write(sc, 22, rf);

	rt3090_rf_write(sc, 42, rt3090_rf_read(sc, 42) | RT5390_RX_CTB);
	rt3090_rf_write(sc, 20, rt3090_rf_read(sc, 20) & ~0x77);
	rt3090_rf_write(sc, 3, rt3090_rf_read(sc, 3) | RT3593_VCOCAL);

	if (sc->patch_dac && sc->mac_rev < 0x0211) {
		tmp = RAL_READ(sc, RT3070_LDO_CFG0);
		tmp = (tmp & ~0x1f000000) | 0x0d000000;
		RAL_WRITE(sc, RT3070_LDO_CFG0, tmp);
	}
}