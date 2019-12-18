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
struct rtwn_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  msecs_to_ticks (int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
rtwn_usb_delay(struct rtwn_softc *sc, int usec)
{

	/* 1ms delay as default is too big. */
	if (usec < 1000)
		DELAY(usec);
	else
		usb_pause_mtx(&sc->sc_mtx, msecs_to_ticks(usec / 1000));
}