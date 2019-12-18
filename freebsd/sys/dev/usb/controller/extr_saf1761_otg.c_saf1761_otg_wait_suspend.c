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
typedef  scalar_t__ uint8_t ;
struct saf1761_otg_softc {int /*<<< orphan*/  sc_intr_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOTG_DCINTERRUPT_EN ; 
 int /*<<< orphan*/  SOTG_DCINTERRUPT_IERESM ; 
 int /*<<< orphan*/  SOTG_DCINTERRUPT_IESUSP ; 

__attribute__((used)) static void
saf1761_otg_wait_suspend(struct saf1761_otg_softc *sc, uint8_t on)
{
	if (on) {
		sc->sc_intr_enable |= SOTG_DCINTERRUPT_IESUSP;
		sc->sc_intr_enable &= ~SOTG_DCINTERRUPT_IERESM;
	} else {
		sc->sc_intr_enable &= ~SOTG_DCINTERRUPT_IESUSP;
		sc->sc_intr_enable |= SOTG_DCINTERRUPT_IERESM;
	}
	SAF1761_WRITE_LE_4(sc, SOTG_DCINTERRUPT_EN, sc->sc_intr_enable);
}