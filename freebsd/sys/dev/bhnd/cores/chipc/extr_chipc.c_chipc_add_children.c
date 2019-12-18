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
typedef  int u_int ;
struct TYPE_2__ {scalar_t__ nvram_src; int /*<<< orphan*/  flash_type; int /*<<< orphan*/  num_uarts; scalar_t__ pwr_ctrl; int /*<<< orphan*/  aob; scalar_t__ pmu; } ;
struct chipc_softc {int /*<<< orphan*/  dev; TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ BHND_ATTACH_NATIVE ; 
 scalar_t__ BHND_NVRAM_SRC_OTP ; 
 scalar_t__ BHND_NVRAM_SRC_SPROM ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  CHIPC_SFLASH_BASE ; 
 int /*<<< orphan*/  CHIPC_SFLASH_SIZE ; 
 int /*<<< orphan*/  CHIPC_SPROM_OTP ; 
 int /*<<< orphan*/  CHIPC_SPROM_OTP_SIZE ; 
 int /*<<< orphan*/  CHIPC_UART (int) ; 
 int /*<<< orphan*/  CHIPC_UART_MAX ; 
 int /*<<< orphan*/  CHIPC_UART_SIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  RM_MAX_END ; 
 scalar_t__ bhnd_get_attach_type (int /*<<< orphan*/ ) ; 
 char* chipc_flash_bus_name (int /*<<< orphan*/ ) ; 
 int chipc_set_irq_resource (struct chipc_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int chipc_set_mem_resource (struct chipc_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_add_children(struct chipc_softc *sc)
{
	device_t	 child;
	const char	*flash_bus;
	int		 error;

	/* SPROM/OTP */
	if (sc->caps.nvram_src == BHND_NVRAM_SRC_SPROM ||
	    sc->caps.nvram_src == BHND_NVRAM_SRC_OTP)
	{
		child = BUS_ADD_CHILD(sc->dev, 0, "bhnd_nvram", -1);
		if (child == NULL) {
			device_printf(sc->dev, "failed to add nvram device\n");
			return (ENXIO);
		}

		/* Both OTP and external SPROM are mapped at CHIPC_SPROM_OTP */
		error = chipc_set_mem_resource(sc, child, 0, CHIPC_SPROM_OTP,
		    CHIPC_SPROM_OTP_SIZE, 0, 0);
		if (error) {
			device_printf(sc->dev, "failed to set OTP memory "
			    "resource: %d\n", error);
			return (error);
		}
	}

	/*
	 * PMU/PWR_CTRL
	 * 
	 * On AOB ("Always on Bus") devices, the PMU core (if it exists) is
	 * attached directly to the bhnd(4) bus -- not chipc.
	 */
	if (sc->caps.pmu && !sc->caps.aob) {
		child = BUS_ADD_CHILD(sc->dev, 0, "bhnd_pmu", -1);
		if (child == NULL) {
			device_printf(sc->dev, "failed to add pmu\n");
			return (ENXIO);
		}
	} else if (sc->caps.pwr_ctrl) {
		child = BUS_ADD_CHILD(sc->dev, 0, "bhnd_pwrctl", -1);
		if (child == NULL) {
			device_printf(sc->dev, "failed to add pwrctl\n");
			return (ENXIO);
		}
	}

	/* GPIO */
	child = BUS_ADD_CHILD(sc->dev, 0, "gpio", -1);
	if (child == NULL) {
		device_printf(sc->dev, "failed to add gpio\n");
		return (ENXIO);
	}

	error = chipc_set_mem_resource(sc, child, 0, 0, RM_MAX_END, 0, 0);
	if (error) {
		device_printf(sc->dev, "failed to set gpio memory resource: "
		    "%d\n", error);
		return (error);
	}

	/* All remaining devices are SoC-only */
	if (bhnd_get_attach_type(sc->dev) != BHND_ATTACH_NATIVE)
		return (0);

	/* UARTs */
	for (u_int i = 0; i < min(sc->caps.num_uarts, CHIPC_UART_MAX); i++) {
		int irq_rid, mem_rid;

		irq_rid = 0;
		mem_rid = 0;

		child = BUS_ADD_CHILD(sc->dev, 0, "uart", -1);
		if (child == NULL) {
			device_printf(sc->dev, "failed to add uart%u\n", i);
			return (ENXIO);
		}

		/* Shared IRQ */
		error = chipc_set_irq_resource(sc, child, irq_rid, 0);
		if (error) {
			device_printf(sc->dev, "failed to set uart%u irq %u\n",
			    i, 0);
			return (error);
		}

		/* UART registers are mapped sequentially */
		error = chipc_set_mem_resource(sc, child, mem_rid,
		    CHIPC_UART(i), CHIPC_UART_SIZE, 0, 0);
		if (error) {
			device_printf(sc->dev, "failed to set uart%u memory "
			    "resource: %d\n", i, error);
			return (error);
		}
	}

	/* Flash */
	flash_bus = chipc_flash_bus_name(sc->caps.flash_type);
	if (flash_bus != NULL) {
		int rid;

		child = BUS_ADD_CHILD(sc->dev, 0, flash_bus, -1);
		if (child == NULL) {
			device_printf(sc->dev, "failed to add %s device\n",
			    flash_bus);
			return (ENXIO);
		}

		/* flash memory mapping */
		rid = 0;
		error = chipc_set_mem_resource(sc, child, rid, 0, RM_MAX_END, 1,
		    1);
		if (error) {
			device_printf(sc->dev, "failed to set flash memory "
			    "resource %d: %d\n", rid, error);
			return (error);
		}

		/* flashctrl registers */
		rid++;
		error = chipc_set_mem_resource(sc, child, rid,
		    CHIPC_SFLASH_BASE, CHIPC_SFLASH_SIZE, 0, 0);
		if (error) {
			device_printf(sc->dev, "failed to set flash memory "
			    "resource %d: %d\n", rid, error);
			return (error);
		}
	}

	return (0);
}