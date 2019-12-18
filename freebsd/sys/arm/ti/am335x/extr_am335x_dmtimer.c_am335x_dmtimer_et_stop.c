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
struct eventtimer {struct am335x_dmtimer_softc* et_priv; } ;
struct am335x_dmtimer_softc {int tclr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMTIMER_WRITE4 (struct am335x_dmtimer_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMT_IRQENABLE_CLR ; 
 int /*<<< orphan*/  DMT_IRQSTATUS ; 
 int DMT_IRQ_OVF ; 
 int /*<<< orphan*/  DMT_TCLR ; 
 int DMT_TCLR_AUTOLOAD ; 
 int DMT_TCLR_START ; 

__attribute__((used)) static int
am335x_dmtimer_et_stop(struct eventtimer *et)
{
	struct am335x_dmtimer_softc *sc;

	sc = et->et_priv;

	/* Stop timer, disable and clear interrupt. */
	sc->tclr &= ~(DMT_TCLR_START | DMT_TCLR_AUTOLOAD);
	DMTIMER_WRITE4(sc, DMT_TCLR, sc->tclr);
	DMTIMER_WRITE4(sc, DMT_IRQENABLE_CLR, DMT_IRQ_OVF);
	DMTIMER_WRITE4(sc, DMT_IRQSTATUS, DMT_IRQ_OVF);
	return (0);
}