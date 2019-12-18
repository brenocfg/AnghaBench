#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct uart_class {int dummy; } ;
struct TYPE_4__ {struct uart_class* sc_class; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct snps_softc {int /*<<< orphan*/  reset; int /*<<< orphan*/ * apb_pclk; int /*<<< orphan*/ * baudclk; TYPE_2__ ns8250; } ;
typedef  int /*<<< orphan*/  shift ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  iowidth ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clock ;
typedef  int /*<<< orphan*/ * clk_t ;
struct TYPE_6__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  UART_F_BUSY_DETECT ; 
 scalar_t__ bootverbose ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_freq (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  compat_data ; 
 struct snps_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_3__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 scalar_t__ snps_get_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snps_probe(device_t dev)
{
	struct snps_softc *sc;
	struct uart_class *uart_class;
	phandle_t node;
	uint32_t shift, iowidth, clock;
	uint64_t freq;
	int error;
#ifdef EXT_RESOURCES
	clk_t baudclk, apb_pclk;
	hwreset_t reset;
#endif

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	uart_class = (struct uart_class *)ofw_bus_search_compatible(dev,
	    compat_data)->ocd_data;
	if (uart_class == NULL)
		return (ENXIO);

	freq = 0;
	sc = device_get_softc(dev);
	sc->ns8250.base.sc_class = uart_class;

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "reg-shift", &shift, sizeof(shift)) <= 0)
		shift = 0;
	if (OF_getencprop(node, "reg-io-width", &iowidth, sizeof(iowidth)) <= 0)
		iowidth = 1;
	if (OF_getencprop(node, "clock-frequency", &clock, sizeof(clock)) <= 0)
		clock = 0;

#ifdef EXT_RESOURCES
	if (hwreset_get_by_ofw_idx(dev, 0, 0, &reset) == 0) {
		error = hwreset_deassert(reset);
		if (error != 0) {
			device_printf(dev, "cannot de-assert reset\n");
			return (error);
		}
	}

	if (snps_get_clocks(dev, &baudclk, &apb_pclk) == 0) {
		error = clk_enable(baudclk);
		if (error != 0) {
			device_printf(dev, "cannot enable baud clock\n");
			return (error);
		}
		if (apb_pclk != NULL) {
			error = clk_enable(apb_pclk);
			if (error != 0) {
				device_printf(dev,
				    "cannot enable peripheral clock\n");
				return (error);
			}
		}

		if (clock == 0) {
			error = clk_get_freq(baudclk, &freq);
			if (error != 0) {
				device_printf(dev, "cannot get frequency\n");
				return (error);
			}
			clock = (uint32_t)freq;
		}
	}
#endif

	if (bootverbose && clock == 0)
		device_printf(dev, "could not determine frequency\n");

	error = uart_bus_probe(dev, (int)shift, (int)iowidth, (int)clock, 0, 0, UART_F_BUSY_DETECT);
	if (error != 0)
		return (error);

#ifdef EXT_RESOURCES
	/* XXX uart_bus_probe has changed the softc, so refresh it */
	sc = device_get_softc(dev);

	/* Store clock and reset handles for detach */
	sc->baudclk = baudclk;
	sc->apb_pclk = apb_pclk;
	sc->reset = reset;
#endif

	return (0);
}