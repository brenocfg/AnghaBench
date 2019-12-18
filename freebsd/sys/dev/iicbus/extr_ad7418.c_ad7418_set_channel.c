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
struct ad7418_softc {int sc_curchan; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7418_CONF ; 
 int AD7418_CONF_CHAN ; 
 int ad7418_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7418_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hz ; 
 int /*<<< orphan*/  tsleep (struct ad7418_softc*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ad7418_set_channel(struct ad7418_softc *sc, int chan)
{
	if (sc->sc_curchan == chan)
		return;
	ad7418_write_1(sc->sc_dev, AD7418_CONF, 
	    (ad7418_read_1(sc->sc_dev, AD7418_CONF) &~ AD7418_CONF_CHAN)|chan);
	sc->sc_curchan = chan;
#if 0
	/*
	 * NB: Linux driver delays here but chip data sheet
	 *     says nothing and things appear to work fine w/o
	 *     a delay on channel change.
	 */
	/* let channel change settle, 1 tick should be 'nuf (need ~1ms) */
	tsleep(sc, 0, "ad7418", hz/1000);
#endif
}