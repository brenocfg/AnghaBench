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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct aw_pwm_softc {int clk_freq; int enabled; int period; int duty; int /*<<< orphan*/  busdev; int /*<<< orphan*/  res; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_PWM_CTRL ; 
 int AW_PWM_CTRL_EN ; 
 int AW_PWM_CTRL_GATE ; 
 int AW_PWM_CTRL_PRESCALE_MASK ; 
 int /*<<< orphan*/  AW_PWM_PERIOD ; 
 int AW_PWM_PERIOD_ACTIVE_MASK ; 
 int AW_PWM_PERIOD_ACTIVE_SHIFT ; 
 int AW_PWM_PERIOD_TOTAL_MASK ; 
 int AW_PWM_PERIOD_TOTAL_SHIFT ; 
 int AW_PWM_READ (struct aw_pwm_softc*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int NS_PER_SEC ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int* aw_pwm_clk_prescaler ; 
 int /*<<< orphan*/  aw_pwm_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_pwm_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_get_freq (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct aw_pwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int nitems (int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_pwm_attach(device_t dev)
{
	struct aw_pwm_softc *sc;
	uint64_t clk_freq;
	uint32_t reg;
	phandle_t node;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	error = clk_get_by_ofw_index(dev, 0, 0, &sc->clk);
	if (error != 0) {
		device_printf(dev, "cannot get clock\n");
		goto fail;
	}
	error = clk_enable(sc->clk);
	if (error != 0) {
		device_printf(dev, "cannot enable clock\n");
		goto fail;
	}

	error = clk_get_freq(sc->clk, &sc->clk_freq);
	if (error != 0) {
		device_printf(dev, "cannot get clock frequency\n");
		goto fail;
	}

	if (bus_alloc_resources(dev, aw_pwm_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		error = ENXIO;
		goto fail;
	}

	/* Read the configuration left by U-Boot */
	reg = AW_PWM_READ(sc, AW_PWM_CTRL);
	if (reg & (AW_PWM_CTRL_GATE | AW_PWM_CTRL_EN))
		sc->enabled = true;

	reg = AW_PWM_READ(sc, AW_PWM_CTRL);
	reg &= AW_PWM_CTRL_PRESCALE_MASK;
	if (reg > nitems(aw_pwm_clk_prescaler)) {
		device_printf(dev, "Bad prescaler %x, cannot guess current settings\n", reg);
		goto skipcfg;
	}
	clk_freq = sc->clk_freq / aw_pwm_clk_prescaler[reg];

	reg = AW_PWM_READ(sc, AW_PWM_PERIOD);
	sc->period = NS_PER_SEC /
		(clk_freq / ((reg >> AW_PWM_PERIOD_TOTAL_SHIFT) & AW_PWM_PERIOD_TOTAL_MASK));
	sc->duty = NS_PER_SEC /
		(clk_freq / ((reg >> AW_PWM_PERIOD_ACTIVE_SHIFT) & AW_PWM_PERIOD_ACTIVE_MASK));

skipcfg:
	/*
	 * Note that we don't check for failure to attach pwmbus -- even without
	 * it we can still service clients who connect via fdt xref data.
	 */
	node = ofw_bus_get_node(dev);
	OF_device_register_xref(OF_xref_from_node(node), dev);

	sc->busdev = device_add_child(dev, "pwmbus", -1);

	return (bus_generic_attach(dev));

fail:
	aw_pwm_detach(dev);
	return (error);
}