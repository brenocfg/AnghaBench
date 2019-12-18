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
struct cs4231_softc {int sc_burst; int sc_nmres; int sc_nires; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_SBUS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SBUS_BURST_16 ; 
 int SBUS_BURST_32 ; 
 int SBUS_BURST_64 ; 
 int cs4231_attach_common (struct cs4231_softc*) ; 
 struct cs4231_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int sbus_get_burstsz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4231_sbus_attach(device_t dev)
{
	struct cs4231_softc *sc;
	int burst;

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->sc_dev = dev;
	/*
	 * XXX
	 * No public documentation exists on programming burst size of APCDMA.
	 */
	burst = sbus_get_burstsz(sc->sc_dev);
	if ((burst & SBUS_BURST_64))
		sc->sc_burst = 64;
	else if ((burst & SBUS_BURST_32))
		sc->sc_burst = 32;
	else if ((burst & SBUS_BURST_16))
		sc->sc_burst = 16;
	else
		sc->sc_burst = 0;
	sc->sc_flags = CS4231_SBUS;
	sc->sc_nmres = 1;
	sc->sc_nires = 1;
	return cs4231_attach_common(sc);
}