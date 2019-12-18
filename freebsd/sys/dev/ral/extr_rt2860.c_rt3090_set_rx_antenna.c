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
typedef  int uint32_t ;
struct rt2860_softc {int mac_ver; } ;

/* Variables and functions */
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2860_C ; 
 int /*<<< orphan*/  RT2860_GPIO_CTRL ; 
 int /*<<< orphan*/  RT2860_PCI_EECTRL ; 
 int rt2860_mcu_bbp_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt2860_mcu_bbp_write (struct rt2860_softc*,int,int) ; 

__attribute__((used)) static void
rt3090_set_rx_antenna(struct rt2860_softc *sc, int aux)
{
	uint32_t tmp;

	if (aux) {
		if (sc->mac_ver == 0x5390) {
			rt2860_mcu_bbp_write(sc, 152, 
			    rt2860_mcu_bbp_read(sc, 152) & ~0x80);
		} else {
			tmp = RAL_READ(sc, RT2860_PCI_EECTRL);
			RAL_WRITE(sc, RT2860_PCI_EECTRL, tmp & ~RT2860_C);
			tmp = RAL_READ(sc, RT2860_GPIO_CTRL);
			RAL_WRITE(sc, RT2860_GPIO_CTRL, (tmp & ~0x0808) | 0x08);
		}
	} else {
		if (sc->mac_ver == 0x5390) {
			rt2860_mcu_bbp_write(sc, 152, 
			    rt2860_mcu_bbp_read(sc, 152) | 0x80);
		} else {
			tmp = RAL_READ(sc, RT2860_PCI_EECTRL);
			RAL_WRITE(sc, RT2860_PCI_EECTRL, tmp | RT2860_C);
			tmp = RAL_READ(sc, RT2860_GPIO_CTRL);
			RAL_WRITE(sc, RT2860_GPIO_CTRL, tmp & ~0x0808);
		}
	}
}