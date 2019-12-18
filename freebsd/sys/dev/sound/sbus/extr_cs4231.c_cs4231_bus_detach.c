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
struct cs4231_channel {scalar_t__ locked; } ;
struct cs4231_softc {int sc_flags; struct cs4231_channel sc_pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CS4231_EBUS ; 
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  cs4231_ebdma_reset (struct cs4231_softc*) ; 
 int /*<<< orphan*/  cs4231_free_resource (struct cs4231_softc*) ; 
 struct cs4231_softc* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4231_bus_detach(device_t dev)
{
	struct cs4231_softc *sc;
	struct cs4231_channel *pch, *rch;
	int error;

	sc = pcm_getdevinfo(dev);
	CS4231_LOCK(sc);
	pch = &sc->sc_pch;
	rch = &sc->sc_pch;
	if (pch->locked || rch->locked) {
		CS4231_UNLOCK(sc);
		return (EBUSY);
	}
	/*
	 * Since EBDMA requires valid DMA buffer to drain its FIFO, we need
	 * real DMA buffer for draining.
	 */
	if ((sc->sc_flags & CS4231_EBUS) != 0)
		cs4231_ebdma_reset(sc);
	CS4231_UNLOCK(sc);
	error = pcm_unregister(dev);
	if (error)
		return (error);
	cs4231_free_resource(sc);
	return (0);
}