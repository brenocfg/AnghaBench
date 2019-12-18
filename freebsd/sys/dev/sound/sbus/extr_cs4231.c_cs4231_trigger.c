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
struct cs4231_softc {int sc_flags; } ;
struct cs4231_channel {struct cs4231_softc* parent; } ;

/* Variables and functions */
 int CS4231_SBUS ; 
 int /*<<< orphan*/  cs4231_apcdma_trigger (struct cs4231_softc*,struct cs4231_channel*) ; 
 int /*<<< orphan*/  cs4231_ebdma_trigger (struct cs4231_softc*,struct cs4231_channel*) ; 

__attribute__((used)) static void
cs4231_trigger(struct cs4231_channel *ch)
{
	struct cs4231_softc *sc;

	sc = ch->parent;
	if ((sc->sc_flags & CS4231_SBUS) != 0)
		cs4231_apcdma_trigger(sc, ch);
	else
		cs4231_ebdma_trigger(sc, ch);
}