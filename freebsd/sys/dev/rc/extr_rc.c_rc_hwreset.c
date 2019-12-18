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
typedef  int u_int ;
struct rc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCRCMD (struct rc_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR_HWRESET ; 
 int /*<<< orphan*/  CD180_GICR ; 
 int /*<<< orphan*/  CD180_GIVR ; 
 int /*<<< orphan*/  CD180_PILR1 ; 
 int /*<<< orphan*/  CD180_PILR2 ; 
 int /*<<< orphan*/  CD180_PILR3 ; 
 int /*<<< orphan*/  CD180_PPRH ; 
 int /*<<< orphan*/  CD180_PPRL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RC_CTOUT ; 
 int /*<<< orphan*/  RC_DTREG ; 
 int RC_OSCFREQ ; 
 int RC_PILR_MODEM ; 
 int RC_PILR_RX ; 
 int RC_PILR_TX ; 
 int /*<<< orphan*/  WAITFORCCR (struct rc_softc*,int) ; 
 int /*<<< orphan*/  rcout (struct rc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rc_hwreset(struct rc_softc *sc, u_int chipid)
{
	CCRCMD(sc, -1, CCR_HWRESET);            /* Hardware reset */
	DELAY(20000);
	WAITFORCCR(sc, -1);

	rcout(sc, RC_CTOUT, 0);             /* Clear timeout  */
	rcout(sc, CD180_GIVR,  chipid);
	rcout(sc, CD180_GICR,  0);

	/* Set Prescaler Registers (1 msec) */
	rcout(sc, CD180_PPRL, ((RC_OSCFREQ + 999) / 1000) & 0xFF);
	rcout(sc, CD180_PPRH, ((RC_OSCFREQ + 999) / 1000) >> 8);

	/* Initialize Priority Interrupt Level Registers */
	rcout(sc, CD180_PILR1, RC_PILR_MODEM);
	rcout(sc, CD180_PILR2, RC_PILR_TX);
	rcout(sc, CD180_PILR3, RC_PILR_RX);

	/* Reset DTR */
	rcout(sc, RC_DTREG, ~0);
}