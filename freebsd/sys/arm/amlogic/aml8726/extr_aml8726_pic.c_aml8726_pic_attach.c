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
struct aml8726_pic_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AML_PIC_0_FIRQ_SEL ; 
 scalar_t__ AML_PIC_0_MASK_REG ; 
 scalar_t__ AML_PIC_0_STAT_CLR_REG ; 
 int AML_PIC_NCNTRLS ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_pic_softc*,scalar_t__,unsigned int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  aml8726_pic_eoi ; 
 struct aml8726_pic_softc* aml8726_pic_sc ; 
 int /*<<< orphan*/  aml8726_pic_spec ; 
 int /*<<< orphan*/  arm_post_filter ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aml8726_pic_attach(device_t dev)
{
	struct aml8726_pic_softc *sc = device_get_softc(dev);
	int i;

	/* There should be exactly one instance. */
	if (aml8726_pic_sc != NULL)
		return (ENXIO);

	sc->dev = dev;

	if (bus_alloc_resources(dev, aml8726_pic_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	/*
	 * Disable, clear, and set the interrupts to normal mode.
	 */
	for (i = 0; i < AML_PIC_NCNTRLS; i++) {
		CSR_WRITE_4(sc, AML_PIC_0_MASK_REG + i * 16, 0);
		CSR_WRITE_4(sc, AML_PIC_0_STAT_CLR_REG + i * 16, ~0u);
		CSR_WRITE_4(sc, AML_PIC_0_FIRQ_SEL + i * 16, 0);
	}

#ifndef DEV_GIC
	arm_post_filter = aml8726_pic_eoi;
#else
	device_printf(dev, "disabled in favor of gic\n");
#endif

	aml8726_pic_sc = sc;

	return (0);
}