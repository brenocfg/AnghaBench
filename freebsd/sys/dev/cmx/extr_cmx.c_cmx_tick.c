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
struct cmx_softc {int /*<<< orphan*/  ch; int /*<<< orphan*/  sel; scalar_t__ polling; int /*<<< orphan*/  dev; int /*<<< orphan*/  dying; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSRBITS ; 
 int /*<<< orphan*/  BSR_BULK_IN_FULL ; 
 int /*<<< orphan*/  CMX_LOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  CMX_UNLOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  DEBUG_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLL_TICKS ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct cmx_softc*) ; 
 int /*<<< orphan*/  cmx_read_BSR (struct cmx_softc*) ; 
 scalar_t__ cmx_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmx_tick(void *xsc)
{
	struct cmx_softc *sc = xsc;
	uint8_t bsr;

	CMX_LOCK(sc);
	if (sc->polling && !sc->dying) {
		bsr = cmx_read_BSR(sc);
		DEBUG_printf(sc->dev, "BSR=%b\n", bsr, BSRBITS);
		if (cmx_test(bsr, BSR_BULK_IN_FULL, 1)) {
			sc->polling = 0;
			selwakeuppri(&sc->sel, PZERO);
		} else {
			callout_reset(&sc->ch, POLL_TICKS, cmx_tick, sc);
		}
	}
	CMX_UNLOCK(sc);
}