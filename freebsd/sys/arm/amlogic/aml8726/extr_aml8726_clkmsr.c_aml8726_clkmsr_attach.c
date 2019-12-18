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
struct aml8726_clkmsr_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_CLKMSR_CLK81 ; 
 int ENXIO ; 
 int aml8726_clkmsr_clock_frequency (struct aml8726_clkmsr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_clkmsr_fixup_clk81 (struct aml8726_clkmsr_softc*,int) ; 
 int /*<<< orphan*/  aml8726_clkmsr_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_clkmsr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
aml8726_clkmsr_attach(device_t dev)
{
	struct aml8726_clkmsr_softc *sc = device_get_softc(dev);
	int freq;

	sc->dev = dev;

	if (bus_alloc_resources(dev, aml8726_clkmsr_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	freq = aml8726_clkmsr_clock_frequency(sc, AML_CLKMSR_CLK81);
	device_printf(sc->dev, "bus clock %u MHz\n", freq);

	aml8726_clkmsr_fixup_clk81(sc, freq * 1000000);

	return (0);
}