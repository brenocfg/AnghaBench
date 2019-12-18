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
struct am335x_pwmss_softc {int sc_clk; int /*<<< orphan*/  sc_dev; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int INVALID_CLK_IDENT ; 
 int OF_child (int) ; 
 int OF_peer (int) ; 
#define  PWMSS0_CLK 130 
#define  PWMSS1_CLK 129 
#define  PWMSS2_CLK 128 
 int /*<<< orphan*/  SCM_PWMSS_CTRL ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 struct am335x_pwmss_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,int) ; 
 int ti_hwmods_get_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (int) ; 
 int /*<<< orphan*/  ti_scm_reg_read_4 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ti_scm_reg_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
am335x_pwmss_attach(device_t dev)
{
	struct am335x_pwmss_softc *sc;
	uint32_t reg, id;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->sc_clk = ti_hwmods_get_clock(dev);
	if (sc->sc_clk == INVALID_CLK_IDENT) {
		device_printf(dev, "failed to get device id based on ti,hwmods\n");
		return (EINVAL);
	}

	ti_prcm_clk_enable(sc->sc_clk);
	ti_scm_reg_read_4(SCM_PWMSS_CTRL, &reg);
	switch (sc->sc_clk) {
		case PWMSS0_CLK:
			id = 0;
			break;
		case PWMSS1_CLK:
			id = 1;
			break;

		case PWMSS2_CLK:
			id = 2;
			break;
		default:
			device_printf(dev, "unknown pwmss clock id: %d\n", sc->sc_clk);
			return (EINVAL);
	}
	reg |= (1 << id);
	ti_scm_reg_write_4(SCM_PWMSS_CTRL, reg);

	node = ofw_bus_get_node(dev);

	if (node == -1)
		return (ENXIO);

	simplebus_init(dev, node);

	/*
	 * Allow devices to identify.
	 */
	bus_generic_probe(dev);

	/*
	 * Now walk the OFW tree and attach top-level devices.
	 */
	for (node = OF_child(node); node > 0; node = OF_peer(node))
		simplebus_add_device(dev, node, 0, NULL, -1, NULL);

	return (bus_generic_attach(dev));
}