#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {TYPE_1__ ppsparam; } ;
struct dmtpps_softc {int pps_curmode; int /*<<< orphan*/  tclr; TYPE_2__ pps_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMTIMER_WRITE4 (struct dmtpps_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMT_TCLR ; 
 int /*<<< orphan*/  DMT_TCLR_CAPTRAN_LOHI ; 
 int /*<<< orphan*/  DMT_TCLR_CAPTRAN_MASK ; 
 int PPS_CAPTUREASSERT ; 

__attribute__((used)) static void
dmtpps_set_hw_capture(struct dmtpps_softc *sc, bool force_off)
{
	int newmode;

	if (force_off)
		newmode = 0;
	else
		newmode = sc->pps_state.ppsparam.mode & PPS_CAPTUREASSERT;

	if (newmode == sc->pps_curmode)
		return;
	sc->pps_curmode = newmode;

	if (newmode == PPS_CAPTUREASSERT)
		sc->tclr |= DMT_TCLR_CAPTRAN_LOHI;
	else
		sc->tclr &= ~DMT_TCLR_CAPTRAN_MASK;
	DMTIMER_WRITE4(sc, DMT_TCLR, sc->tclr);
}