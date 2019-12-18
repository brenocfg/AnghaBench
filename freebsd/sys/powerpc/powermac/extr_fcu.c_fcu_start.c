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
struct fcu_softc {int /*<<< orphan*/  enum_hook; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct fcu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fcu_attach_fans (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcu_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int fcu_rpm_shift ; 
 int /*<<< orphan*/  fcu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,int) ; 

__attribute__((used)) static void
fcu_start(void *xdev)
{
	unsigned char buf[1] = { 0xff };
	struct fcu_softc *sc;

	device_t dev = (device_t)xdev;

	sc = device_get_softc(dev);

	/* Start the fcu device. */
	fcu_write(sc->sc_dev, sc->sc_addr, 0xe, buf, 1);
	fcu_write(sc->sc_dev, sc->sc_addr, 0x2e, buf, 1);
	fcu_read_1(sc->sc_dev, sc->sc_addr, 0, buf);
	fcu_rpm_shift = (buf[0] == 1) ? 2 : 3;

	device_printf(dev, "FCU initialized, RPM shift: %d\n",
		      fcu_rpm_shift);

	/* Detect and attach child devices. */

	fcu_attach_fans(dev);

	config_intrhook_disestablish(&sc->enum_hook);

}