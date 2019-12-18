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
struct TYPE_2__ {int pud_ctrl; int /*<<< orphan*/  ppin; int /*<<< orphan*/  func; } ;
struct aml8726_pinctrl_softc {int /*<<< orphan*/  res; TYPE_1__ soc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_PINCTRL_LOCK_INIT (struct aml8726_pinctrl_softc*) ; 
#define  AML_SOC_HW_REV_M3 131 
#define  AML_SOC_HW_REV_M6 130 
#define  AML_SOC_HW_REV_M8 129 
#define  AML_SOC_HW_REV_M8B 128 
 int ENXIO ; 
 int /*<<< orphan*/  aml8726_m3_pinctrl ; 
 int /*<<< orphan*/  aml8726_m3_pkg_pin ; 
 int /*<<< orphan*/  aml8726_m6_pinctrl ; 
 int /*<<< orphan*/  aml8726_m6_pkg_pin ; 
 int /*<<< orphan*/  aml8726_m8_pinctrl ; 
 int /*<<< orphan*/  aml8726_m8_pkg_pin ; 
 int /*<<< orphan*/  aml8726_m8b_pinctrl ; 
 int /*<<< orphan*/  aml8726_m8b_pkg_pin ; 
 int /*<<< orphan*/  aml8726_pinctrl_spec ; 
 int aml8726_soc_hw_rev ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_pinctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aml8726_pinctrl_attach(device_t dev)
{
	struct aml8726_pinctrl_softc *sc = device_get_softc(dev);

	sc->dev = dev;

	sc->soc.pud_ctrl = false;

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M3:
		sc->soc.func = aml8726_m3_pinctrl;
		sc->soc.ppin = aml8726_m3_pkg_pin;
		break;
	case AML_SOC_HW_REV_M6:
		sc->soc.func = aml8726_m6_pinctrl;
		sc->soc.ppin = aml8726_m6_pkg_pin;
		break;
	case AML_SOC_HW_REV_M8:
		sc->soc.func = aml8726_m8_pinctrl;
		sc->soc.ppin = aml8726_m8_pkg_pin;
		sc->soc.pud_ctrl = true;
		break;
	case AML_SOC_HW_REV_M8B:
		sc->soc.func = aml8726_m8b_pinctrl;
		sc->soc.ppin = aml8726_m8b_pkg_pin;
		sc->soc.pud_ctrl = true;
		break;
	default:
		device_printf(dev, "unsupported SoC\n");
		return (ENXIO);
		/* NOTREACHED */
	}

	if (bus_alloc_resources(dev, aml8726_pinctrl_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	AML_PINCTRL_LOCK_INIT(sc);

	fdt_pinctrl_register(dev, "amlogic,pins");
	fdt_pinctrl_configure_tree(dev);

	return (0);
}