#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int always; int xo; int gpo; } ;
struct aml8726_rtc_softc {int /*<<< orphan*/  res; TYPE_1__ init; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RTC_LOCK_INIT (struct aml8726_rtc_softc*) ; 
#define  AML_SOC_HW_REV_M3 131 
#define  AML_SOC_HW_REV_M6 130 
#define  AML_SOC_HW_REV_M8 129 
#define  AML_SOC_HW_REV_M8B 128 
 int ENXIO ; 
 scalar_t__ aml8726_rtc_check_xo (struct aml8726_rtc_softc*) ; 
 int /*<<< orphan*/  aml8726_rtc_initialize (struct aml8726_rtc_softc*) ; 
 int /*<<< orphan*/  aml8726_rtc_spec ; 
 int aml8726_soc_hw_rev ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 struct aml8726_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aml8726_rtc_attach(device_t dev)
{
	struct aml8726_rtc_softc *sc = device_get_softc(dev);

	sc->dev = dev;

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M3:
		sc->init.always = true;
		sc->init.xo = 0x3c0a;
		sc->init.gpo = 0x100000;
		break;
	case AML_SOC_HW_REV_M6:
	case AML_SOC_HW_REV_M8:
	case AML_SOC_HW_REV_M8B:
		sc->init.always = false;
		sc->init.xo = 0x180a;
		sc->init.gpo = 0x500000;
		break;
	default:
		device_printf(dev, "unsupported SoC\n");
		return (ENXIO);
		/* NOTREACHED */
	}

	if (bus_alloc_resources(dev, aml8726_rtc_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	aml8726_rtc_initialize(sc);

	if (aml8726_rtc_check_xo(sc) != 0) {
		device_printf(dev, "crystal oscillator check failed\n");

		bus_release_resources(dev, aml8726_rtc_spec, sc->res);

		return (ENXIO);
	}

	AML_RTC_LOCK_INIT(sc);

	clock_register(dev, 1000000);

	return (0);
}