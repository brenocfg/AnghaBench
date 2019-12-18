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
struct run_softc {scalar_t__ rf_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_GPIO_CTRL ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_ANTSEL ; 
 scalar_t__ RT5390_RF_5370 ; 
 int /*<<< orphan*/  run_bbp_read (struct run_softc*,int,int*) ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_mcu_cmd (struct run_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_set_rx_antenna(struct run_softc *sc, int aux)
{
	uint32_t tmp;
	uint8_t bbp152;

	if (aux) {
		if (sc->rf_rev == RT5390_RF_5370) {
			run_bbp_read(sc, 152, &bbp152);
			run_bbp_write(sc, 152, bbp152 & ~0x80);
		} else {
			run_mcu_cmd(sc, RT2860_MCU_CMD_ANTSEL, 0);
			run_read(sc, RT2860_GPIO_CTRL, &tmp);
			run_write(sc, RT2860_GPIO_CTRL, (tmp & ~0x0808) | 0x08);
		}
	} else {
		if (sc->rf_rev == RT5390_RF_5370) {
			run_bbp_read(sc, 152, &bbp152);
			run_bbp_write(sc, 152, bbp152 | 0x80);
		} else {
			run_mcu_cmd(sc, RT2860_MCU_CMD_ANTSEL, 1);
			run_read(sc, RT2860_GPIO_CTRL, &tmp);
			run_write(sc, RT2860_GPIO_CTRL, tmp & ~0x0808);
		}
	}
}