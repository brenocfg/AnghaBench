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
typedef  int u_int8_t ;
struct cs4231_softc {scalar_t__ sc_enabled; int sc_flags; int /*<<< orphan*/  sc_rch; int /*<<< orphan*/  sc_pch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APC_CSR ; 
 int /*<<< orphan*/  APC_CSR_RESET ; 
 int /*<<< orphan*/  APC_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_LOCK_ASSERT (struct cs4231_softc*) ; 
 int CS4231_SBUS ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS_PIN_CONTROL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  cs4231_ebdma_reset (struct cs4231_softc*) ; 
 int /*<<< orphan*/  cs4231_halt (int /*<<< orphan*/ *) ; 
 int cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_write (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cs4231_disable(struct cs4231_softc *sc)
{
	u_int8_t v;

	CS4231_LOCK_ASSERT(sc);

	if (sc->sc_enabled == 0)
		return;
	sc->sc_enabled = 0;
	CS4231_UNLOCK(sc);
	cs4231_halt(&sc->sc_pch);
	cs4231_halt(&sc->sc_rch);
	CS4231_LOCK(sc);
	v = cs4231_read(sc, CS_PIN_CONTROL) & ~INTERRUPT_ENABLE;
	cs4231_write(sc, CS_PIN_CONTROL, v);

	if ((sc->sc_flags & CS4231_SBUS) != 0) {
		APC_WRITE(sc, APC_CSR, APC_CSR_RESET);
		DELAY(10);
		APC_WRITE(sc, APC_CSR, 0);
		DELAY(10);
	} else
		cs4231_ebdma_reset(sc);
}