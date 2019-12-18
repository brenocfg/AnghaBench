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
struct owc_gpiobus_softc {int dummy; } ;
struct ow_timing {int t_pdl; scalar_t__ t_pdh; scalar_t__ t_rsth; scalar_t__ t_rstl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (scalar_t__) ; 
 int EIO ; 
 int GETBUS (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  GETPIN (struct owc_gpiobus_softc*,int*) ; 
 int /*<<< orphan*/  INPIN (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  LOW (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  OUTPIN (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  RELBUS (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct owc_gpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
owc_gpiobus_reset_and_presence(device_t dev, struct ow_timing *t, int *bit)
{
	struct owc_gpiobus_softc *sc;
	int error;
	int buf = -1;

	sc = device_get_softc(dev);
	error = GETBUS(sc);
	if (error != 0)
		return (error);

	/*
	 * Read the current state of the bus. The steady state of an idle bus is
	 * high. Badly wired buses that are missing the required pull up, or
	 * that have a short circuit to ground cause all kinds of mischief when
	 * we try to read them later. Return EIO and release the bus if the bus
	 * is currently low.
	 */
	INPIN(sc);
	GETPIN(sc, &buf);
	if (buf == 0) {
		*bit = -1;
		RELBUS(sc);
		return (EIO);
	}

	critical_enter();

	/* Force low */
	OUTPIN(sc);
	LOW(sc);
	DELAY(t->t_rstl);

	/* Allow resistor to float line high and then wait for reset pulse */
	INPIN(sc);
	DELAY(t->t_pdh + t->t_pdl / 2);

	/* Read presence pulse  */
	GETPIN(sc, &buf);
	*bit = !!buf;

	critical_exit();

	DELAY(t->t_rsth - (t->t_pdh + t->t_pdl / 2));	/* Timing not critical for this one */

	/*
	 * Read the state of the bus after we've waited past the end of the rest
	 * window. It should return to high. If it is low, then we have some
	 * problem and should abort the reset.
	 */
	GETPIN(sc, &buf);
	if (buf == 0) {
		*bit = -1;
		RELBUS(sc);
		return (EIO);
	}

	RELBUS(sc);

	return (0);
}