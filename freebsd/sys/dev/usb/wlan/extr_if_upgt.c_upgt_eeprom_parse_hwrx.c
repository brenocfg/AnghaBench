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
typedef  int /*<<< orphan*/  uint8_t ;
struct upgt_softc {scalar_t__ sc_eeprom_hwrx; } ;
struct upgt_eeprom_option_hwrx {scalar_t__ rxfilter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct upgt_softc*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  UPGT_DEBUG_FW ; 
 scalar_t__ UPGT_EEPROM_RX_CONST ; 

__attribute__((used)) static void
upgt_eeprom_parse_hwrx(struct upgt_softc *sc, uint8_t *data)
{
	struct upgt_eeprom_option_hwrx *option_hwrx;

	option_hwrx = (struct upgt_eeprom_option_hwrx *)data;

	sc->sc_eeprom_hwrx = option_hwrx->rxfilter - UPGT_EEPROM_RX_CONST;

	DPRINTF(sc, UPGT_DEBUG_FW, "hwrx option value=0x%04x\n",
	    sc->sc_eeprom_hwrx);
}