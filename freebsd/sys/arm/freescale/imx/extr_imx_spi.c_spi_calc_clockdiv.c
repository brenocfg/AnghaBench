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
typedef  int u_int ;
struct spi_softc {int basefreq; int debug; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTLREG_POSTDIV_SHIFT ; 
 int CTLREG_PREDIV_SHIFT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 

__attribute__((used)) static u_int
spi_calc_clockdiv(struct spi_softc *sc, u_int busfreq)
{
	u_int post, pre;

	/* Returning 0 effectively sets both dividers to 1. */
	if (sc->basefreq <= busfreq)
		return (0);

	/*
	 * Brute-force this; all real-world bus speeds are going to be found on
	 * the 1st or 2nd time through this loop.
	 */
	for (post = 0; post < 16; ++post) {
		pre = ((sc->basefreq >> post) / busfreq) - 1;
		if (pre < 16)
			break;
	}
	if (post == 16) {
		/* The lowest we can go is ~115 Hz. */
		pre = 15;
		post = 15;
	}

	if (sc->debug >= 2) {
		device_printf(sc->dev,
		    "base %u bus %u; pre %u, post %u; actual busfreq %u\n",
		    sc->basefreq, busfreq, pre, post,
		    (sc->basefreq / (pre + 1)) / (1 << post));
	}

	return (pre << CTLREG_PREDIV_SHIFT) | (post << CTLREG_POSTDIV_SHIFT);
}