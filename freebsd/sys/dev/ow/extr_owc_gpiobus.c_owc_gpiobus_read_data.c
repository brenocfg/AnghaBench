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
struct ow_timing {int t_rdv; int t_slot; int t_rec; int /*<<< orphan*/  t_lowr; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int GETBUS (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  GETPIN (struct owc_gpiobus_softc*,int*) ; 
 int /*<<< orphan*/  INPIN (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  LOW (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  OUTPIN (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  RELBUS (struct owc_gpiobus_softc*) ; 
 int SBT_1US ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct owc_gpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int sbinuptime () ; 

__attribute__((used)) static int
owc_gpiobus_read_data(device_t dev, struct ow_timing *t, int *bit)
{
	struct owc_gpiobus_softc *sc;
	int error, sample;
	sbintime_t then, now;

	sc = device_get_softc(dev);
	error = GETBUS(sc);
	if (error != 0)
		return (error);

	critical_enter();

	/* Force low for t_lowr microseconds */
	then = sbinuptime();
	OUTPIN(sc);
	LOW(sc);
	DELAY(t->t_lowr);

	/*
	 * Slave is supposed to hold the line low for t_rdv microseconds for 0
	 * and immediately float it high for a 1. This is measured from the
	 * master's pushing the line low.
	 */
	INPIN(sc);
	do {
		now = sbinuptime();
		GETPIN(sc, &sample);
	} while (now - then < (t->t_rdv + 2) * SBT_1US && sample == 0);
	critical_exit();

	if (now - then < t->t_rdv * SBT_1US)
		*bit = 1;
	else
		*bit = 0;

	/* Wait out the rest of t_slot */
	do {
		now = sbinuptime();
	} while (now - then < (t->t_slot + t->t_rec) * SBT_1US);

	RELBUS(sc);

	return (error);
}