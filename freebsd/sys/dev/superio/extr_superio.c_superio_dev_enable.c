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
typedef  int /*<<< orphan*/  uint8_t ;
struct superio_devinfo {int ldn; } ;
struct siosc {scalar_t__ vendor; int /*<<< orphan*/  enable_reg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ SUPERIO_VENDOR_ITE ; 
 struct superio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct siosc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_conf_enter (struct siosc*) ; 
 int /*<<< orphan*/  sio_conf_exit (struct siosc*) ; 
 int /*<<< orphan*/  sio_ldn_read (struct siosc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_ldn_write (struct siosc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
superio_dev_enable(device_t dev, uint8_t mask)
{
	device_t sio_dev = device_get_parent(dev);
	struct siosc *sc = device_get_softc(sio_dev);
	struct superio_devinfo *dinfo = device_get_ivars(dev);
	uint8_t v;

	/* GPIO device is always active in ITE chips. */
	if (sc->vendor == SUPERIO_VENDOR_ITE && dinfo->ldn == 7)
		return;

	sio_conf_enter(sc);
	v = sio_ldn_read(sc, dinfo->ldn, sc->enable_reg);
	v |= mask;
	sio_ldn_write(sc, dinfo->ldn, sc->enable_reg, v);
	sio_conf_exit(sc);
}