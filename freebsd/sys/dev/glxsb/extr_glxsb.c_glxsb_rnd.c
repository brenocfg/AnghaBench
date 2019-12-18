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
typedef  int /*<<< orphan*/  value ;
typedef  int uint32_t ;
struct glxsb_softc {int /*<<< orphan*/  sc_rnghz; int /*<<< orphan*/  sc_rngco; int /*<<< orphan*/  sc_sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RANDOM_PURE_GLXSB ; 
 int /*<<< orphan*/  SB_RANDOM_NUM ; 
 int /*<<< orphan*/  SB_RANDOM_NUM_STATUS ; 
 int SB_RNS_TRNG_VALID ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct glxsb_softc*) ; 
 int /*<<< orphan*/  random_harvest_queue (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
glxsb_rnd(void *v)
{
	struct glxsb_softc *sc = v;
	uint32_t status, value;

	status = bus_read_4(sc->sc_sr, SB_RANDOM_NUM_STATUS);
	if (status & SB_RNS_TRNG_VALID) {
		value = bus_read_4(sc->sc_sr, SB_RANDOM_NUM);
		/* feed with one uint32 */
		/* MarkM: FIX!! Check that this does not swamp the harvester! */
		random_harvest_queue(&value, sizeof(value), RANDOM_PURE_GLXSB);
	}

	callout_reset(&sc->sc_rngco, sc->sc_rnghz, glxsb_rnd, sc);
}