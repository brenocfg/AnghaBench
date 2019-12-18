#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mn_softc {scalar_t__ framing; TYPE_1__* f54w; } ;
struct TYPE_2__ {int ipc; int xpm0; int xpm1; int xpm2; int imr0; int imr1; int imr2; int imr3; int imr4; int fmr0; int fmr1; int fmr2; int lim1; int pcd; int pcr; int xsw; int xsp; int xc0; int xc1; int rc0; int rc1; int cmdr; } ;

/* Variables and functions */
 scalar_t__ E1 ; 
 scalar_t__ E1U ; 

__attribute__((used)) static void
f54_init(struct mn_softc *sc)
{
	sc->f54w->ipc  = 0x07;

	sc->f54w->xpm0 = 0xbd;
	sc->f54w->xpm1 = 0x03;
	sc->f54w->xpm2 = 0x00;

	sc->f54w->imr0 = 0x18; /* RMB, CASC */
	sc->f54w->imr1 = 0x08; /* XMB */
	sc->f54w->imr2 = 0x00; 
	sc->f54w->imr3 = 0x38; /* LMFA16, AIS16, RA16 */
	sc->f54w->imr4 = 0x00; 

	sc->f54w->fmr0 = 0xf0; /* X: HDB3, R: HDB3 */
	sc->f54w->fmr1 = 0x0e; /* Send CRC4, 2Mbit, ECM */
	if (sc->framing == E1)
		sc->f54w->fmr2 = 0x03; /* Auto Rem-Alarm, Auto resync */
	else if (sc->framing == E1U)
		sc->f54w->fmr2 = 0x33; /* dais, rtm, Auto Rem-Alarm, Auto resync */

	sc->f54w->lim1 = 0xb0; /* XCLK=8kHz, .62V threshold */
	sc->f54w->pcd =  0x0a;
	sc->f54w->pcr =  0x15;
	sc->f54w->xsw =  0x9f; /* fmr4 */
	if (sc->framing == E1)
		sc->f54w->xsp =  0x1c; /* fmr5 */
	else if (sc->framing == E1U)
		sc->f54w->xsp =  0x3c; /* tt0, fmr5 */
	sc->f54w->xc0 =  0x07;
	sc->f54w->xc1 =  0x3d;
	sc->f54w->rc0 =  0x05;
	sc->f54w->rc1 =  0x00;
	sc->f54w->cmdr = 0x51;
}