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
struct twsi_softc {int need_ack; int /*<<< orphan*/  reg_soft_reset; int /*<<< orphan*/  reg_baud_rate; int /*<<< orphan*/  reg_status; int /*<<< orphan*/  reg_control; int /*<<< orphan*/  reg_slave_ext_addr; int /*<<< orphan*/  reg_slave_addr; int /*<<< orphan*/  reg_data; int /*<<< orphan*/  clk_core; } ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TWI_ADDR ; 
 int /*<<< orphan*/  TWI_CCR ; 
 int /*<<< orphan*/  TWI_CNTR ; 
 int /*<<< orphan*/  TWI_DATA ; 
 int /*<<< orphan*/  TWI_SRST ; 
 int /*<<< orphan*/  TWI_STAT ; 
 int /*<<< orphan*/  TWI_XADDR ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct twsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int twsi_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10_twsi_attach(device_t dev)
{
	struct twsi_softc *sc;
	hwreset_t rst;
	int error;

	sc = device_get_softc(dev);

	/* De-assert reset */
	if (hwreset_get_by_ofw_idx(dev, 0, 0, &rst) == 0) {
		error = hwreset_deassert(rst);
		if (error != 0) {
			device_printf(dev, "could not de-assert reset\n");
			return (error);
		}
	}

	/* Activate clock */
	error = clk_get_by_ofw_index(dev, 0, 0, &sc->clk_core);
	if (error != 0) {
		device_printf(dev, "could not find clock\n");
		return (error);
	}
	error = clk_enable(sc->clk_core);
	if (error != 0) {
		device_printf(dev, "could not enable clock\n");
		return (error);
	}

	sc->reg_data = TWI_DATA;
	sc->reg_slave_addr = TWI_ADDR;
	sc->reg_slave_ext_addr = TWI_XADDR;
	sc->reg_control = TWI_CNTR;
	sc->reg_status = TWI_STAT;
	sc->reg_baud_rate = TWI_CCR;
	sc->reg_soft_reset = TWI_SRST;

	sc->need_ack = true;
	return (twsi_attach(dev));
}