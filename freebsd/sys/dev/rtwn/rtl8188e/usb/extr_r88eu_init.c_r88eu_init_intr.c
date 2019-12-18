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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R88E_HIMR ; 
 int /*<<< orphan*/  R88E_HIMRE ; 
 int R88E_HIMRE_RXERR ; 
 int R88E_HIMRE_RXFOVW ; 
 int R88E_HIMRE_TXERR ; 
 int R88E_HIMRE_TXFOVW ; 
 int R88E_HIMR_CPWM ; 
 int R88E_HIMR_CPWM2 ; 
 int R88E_HIMR_PSTIMEOUT ; 
 int R88E_HIMR_TBDER ; 
 int /*<<< orphan*/  R88E_HISR ; 
 int /*<<< orphan*/  R92C_USB_SPECIAL_OPTION ; 
 int /*<<< orphan*/  R92C_USB_SPECIAL_OPTION_INT_BULK_SEL ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r88eu_init_intr(struct rtwn_softc *sc)
{
	/* TODO: adjust */
	rtwn_write_4(sc, R88E_HISR, 0xffffffff);
	rtwn_write_4(sc, R88E_HIMR, R88E_HIMR_CPWM | R88E_HIMR_CPWM2 |
	    R88E_HIMR_TBDER | R88E_HIMR_PSTIMEOUT);
	rtwn_write_4(sc, R88E_HIMRE, R88E_HIMRE_RXFOVW |
	    R88E_HIMRE_TXFOVW | R88E_HIMRE_RXERR | R88E_HIMRE_TXERR);
	rtwn_setbits_1(sc, R92C_USB_SPECIAL_OPTION, 0,
	    R92C_USB_SPECIAL_OPTION_INT_BULK_SEL);
}