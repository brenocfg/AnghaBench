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
typedef  int /*<<< orphan*/  uint32_t ;
struct ds1631_softc {int init_done; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS1631_CONTROL ; 
 int DS1631_CONTROL_10BIT ; 
 int DS1631_CONTROL_1SHOT ; 
 int /*<<< orphan*/  DS1631_START ; 
 int /*<<< orphan*/  DS1631_STOP ; 
 struct ds1631_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ds1631_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ds1631_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
ds1631_init(device_t dev, uint32_t addr)
{
	uint8_t conf;
	int err;
	struct ds1631_softc *sc;

	sc = device_get_softc(dev);

	err = ds1631_read_1(dev, addr, DS1631_CONTROL, &conf);
	if (err < 0) {
		device_printf(dev, "ds1631 read config failed: %x\n", err);
		return (-1);
	}

	/* Stop the conversion if not in 1SHOT mode. */
	if (conf & ~DS1631_CONTROL_1SHOT)
		err = ds1631_write(dev, addr, DS1631_STOP, &conf, 0);

	/*
	 * Setup the resolution, 10-bit is enough. Each bit increase in
	 * resolution doubles the conversion time.
	 */
	conf = DS1631_CONTROL_10BIT;

	err = ds1631_write(dev, addr, DS1631_CONTROL, &conf, 1);
	if (err < 0) {
		device_printf(dev, "ds1631 write config failed: %x\n", err);
		return (-1);
	}

	/* And now start....*/
	err = ds1631_write(dev, addr, DS1631_START, &conf, 0);

	if (err < 0) {
		device_printf(dev, "ds1631 write start failed: %x\n", err);
		return (-1);
	}

	sc->init_done = 1;

	return (0);

}