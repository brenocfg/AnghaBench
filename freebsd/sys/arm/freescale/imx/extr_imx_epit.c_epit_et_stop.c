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
struct eventtimer {scalar_t__ et_priv; } ;
struct epit_softc {int /*<<< orphan*/  ctlreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIT_CR ; 
 int /*<<< orphan*/  EPIT_SR ; 
 int /*<<< orphan*/  EPIT_SR_OCIF ; 
 int /*<<< orphan*/  WR4 (struct epit_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4B (struct epit_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
epit_et_stop(struct eventtimer *et)
{
	struct epit_softc *sc;

	sc = (struct epit_softc *)et->et_priv;

	/* Disable the timer and clear any pending status. */
	WR4(sc, EPIT_CR, sc->ctlreg);
	WR4B(sc, EPIT_SR, EPIT_SR_OCIF);

	return (0);
}