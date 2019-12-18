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
typedef  int uint32_t ;
struct jz4780_rtc_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ (struct jz4780_rtc_softc*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  JZ_HSPR ; 
 int /*<<< orphan*/  JZ_RTSR ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 struct jz4780_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jz4780_rtc_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_rtc_spec ; 
 int jz4780_rtc_write (struct jz4780_rtc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jz4780_rtc_attach(device_t dev)
{
	struct jz4780_rtc_softc *sc = device_get_softc(dev);
	uint32_t scratch;
	int ret;

	sc->dev = dev;

	if (bus_alloc_resources(dev, jz4780_rtc_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	scratch = CSR_READ(sc, JZ_HSPR);
	if (scratch != 0x12345678) {
		ret = jz4780_rtc_write(sc, JZ_HSPR, 0x12345678);
		if (ret == 0)
			ret = jz4780_rtc_write(sc, JZ_RTSR, 0);
		if (ret) {
			device_printf(dev, "Unable to write RTC registers\n");
			jz4780_rtc_detach(dev);
			return (ret);
		}
	}
	clock_register(dev, 1000000); /* Register 1 HZ clock */
	return (0);
}