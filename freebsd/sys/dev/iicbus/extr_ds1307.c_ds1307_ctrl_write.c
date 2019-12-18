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
typedef  int uint8_t ;
struct ds1307_softc {int sc_ctrl; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1307_CONTROL ; 
 int DS1307_CTRL_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds1307_write1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ds1307_ctrl_write(struct ds1307_softc *sc)
{
	int error;
	uint8_t ctrl;

	ctrl = sc->sc_ctrl & DS1307_CTRL_MASK;
	error = ds1307_write1(sc->sc_dev, DS1307_CONTROL, ctrl);
	if (error != 0)
		device_printf(sc->sc_dev, "cannot write to RTC.\n");

	return (error);
}