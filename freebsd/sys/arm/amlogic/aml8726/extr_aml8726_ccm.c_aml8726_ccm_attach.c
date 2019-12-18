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
struct aml8726_ccm_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  soc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_CCM_LOCK_INIT (struct aml8726_ccm_softc*) ; 
#define  AML_SOC_HW_REV_M3 131 
#define  AML_SOC_HW_REV_M6 130 
#define  AML_SOC_HW_REV_M8 129 
#define  AML_SOC_HW_REV_M8B 128 
 int ENXIO ; 
 int aml8726_ccm_configure_gates (struct aml8726_ccm_softc*) ; 
 int /*<<< orphan*/  aml8726_ccm_spec ; 
 int /*<<< orphan*/  aml8726_m3_ccm ; 
 int /*<<< orphan*/  aml8726_m6_ccm ; 
 int /*<<< orphan*/  aml8726_m8_ccm ; 
 int /*<<< orphan*/  aml8726_m8b_ccm ; 
 int aml8726_soc_hw_rev ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_ccm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aml8726_ccm_attach(device_t dev)
{
	struct aml8726_ccm_softc *sc = device_get_softc(dev);

	sc->dev = dev;

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M3:
		sc->soc = aml8726_m3_ccm;
		break;
	case AML_SOC_HW_REV_M6:
		sc->soc = aml8726_m6_ccm;
		break;
	case AML_SOC_HW_REV_M8:
		sc->soc = aml8726_m8_ccm;
		break;
	case AML_SOC_HW_REV_M8B:
		sc->soc = aml8726_m8b_ccm;
		break;
	default:
		device_printf(dev, "unsupported SoC\n");
		return (ENXIO);
		/* NOTREACHED */
	}

	if (bus_alloc_resources(dev, aml8726_ccm_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	AML_CCM_LOCK_INIT(sc);

	return (aml8726_ccm_configure_gates(sc));
}