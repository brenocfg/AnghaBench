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
struct ow_timing {scalar_t__ t_rec; scalar_t__ t_low0; scalar_t__ t_slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (scalar_t__) ; 
 int GETBUS (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  INPIN (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  LOW (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  OUTPIN (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  RELBUS (struct owc_gpiobus_softc*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct owc_gpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
owc_gpiobus_write_zero(device_t dev, struct ow_timing *t)
{
	struct owc_gpiobus_softc *sc;
	int error;

	sc = device_get_softc(dev);
	error = GETBUS(sc);
	if (error != 0)
		return (error);

	critical_enter();

	/* Force low */
	OUTPIN(sc);
	LOW(sc);
	DELAY(t->t_low0);

	/* Allow resistor to float line high */
	INPIN(sc);
	DELAY(t->t_slot - t->t_low0 + t->t_rec);

	critical_exit();

	RELBUS(sc);

	return (0);
}