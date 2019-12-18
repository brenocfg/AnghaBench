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
typedef  int u_int32_t ;
struct ath_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_ah; scalar_t__ sc_invalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RESET_NOLOSS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ ath_hal_getfatalstate (int /*<<< orphan*/ ,void**,int*) ; 
 int /*<<< orphan*/  ath_reset (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
ath_fatal_proc(void *arg, int pending)
{
	struct ath_softc *sc = arg;
	u_int32_t *state;
	u_int32_t len;
	void *sp;

	if (sc->sc_invalid)
		return;

	device_printf(sc->sc_dev, "hardware error; resetting\n");
	/*
	 * Fatal errors are unrecoverable.  Typically these
	 * are caused by DMA errors.  Collect h/w state from
	 * the hal so we can diagnose what's going on.
	 */
	if (ath_hal_getfatalstate(sc->sc_ah, &sp, &len)) {
		KASSERT(len >= 6*sizeof(u_int32_t), ("len %u bytes", len));
		state = sp;
		device_printf(sc->sc_dev,
		    "0x%08x 0x%08x 0x%08x, 0x%08x 0x%08x 0x%08x\n", state[0],
		    state[1] , state[2], state[3], state[4], state[5]);
	}
	ath_reset(sc, ATH_RESET_NOLOSS);
}