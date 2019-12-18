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
typedef  int uint8_t ;
struct axp8xx_softc {int nregs; int type; int nsensors; int warn_thres; int shut_thres; int /*<<< orphan*/  gpiodev; int /*<<< orphan*/  ih; int /*<<< orphan*/  res; struct axp8xx_regdef* sensors; struct axp8xx_reg_sc** regs; int /*<<< orphan*/ * config; int /*<<< orphan*/  mtx; int /*<<< orphan*/  addr; } ;
struct axp8xx_regdef {char* name; char* format; char* desc; int /*<<< orphan*/  id; } ;
struct axp8xx_reg_sc {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ocd_data; } ;

/* Variables and functions */
#define  AXP803 129 
#define  AXP813 128 
 scalar_t__ AXP_BAP_CAP_WARN_LV1BASE ; 
 int /*<<< orphan*/  AXP_BAT_CAP_WARN ; 
 int AXP_BAT_CAP_WARN_LV1 ; 
 int AXP_BAT_CAP_WARN_LV2 ; 
 int /*<<< orphan*/  AXP_ICTYPE ; 
 int /*<<< orphan*/  AXP_IRQEN1 ; 
 int AXP_IRQEN1_ACIN_HI ; 
 int AXP_IRQEN1_ACIN_LO ; 
 int AXP_IRQEN1_VBUS_HI ; 
 int AXP_IRQEN1_VBUS_LO ; 
 int /*<<< orphan*/  AXP_IRQEN2 ; 
 int AXP_IRQEN2_BATCHGC ; 
 int AXP_IRQEN2_BATCHGD ; 
 int AXP_IRQEN2_BAT_IN ; 
 int AXP_IRQEN2_BAT_NO ; 
 int /*<<< orphan*/  AXP_IRQEN3 ; 
 int /*<<< orphan*/  AXP_IRQEN4 ; 
 int AXP_IRQEN4_BATLVL_LO0 ; 
 int AXP_IRQEN4_BATLVL_LO1 ; 
 int /*<<< orphan*/  AXP_IRQEN5 ; 
 int AXP_IRQEN5_POKLIRQ ; 
 int AXP_IRQEN5_POKSIRQ ; 
 int /*<<< orphan*/  AXP_IRQEN6 ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_AXP8XX_REG ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axp803_config ; 
 struct axp8xx_regdef* axp803_regdefs ; 
 struct axp8xx_regdef* axp813_regdefs ; 
 struct axp8xx_regdef* axp8xx_common_regdefs ; 
 struct axp8xx_regdef* axp8xx_common_sensors ; 
 int /*<<< orphan*/  axp8xx_intr ; 
 scalar_t__ axp8xx_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 struct axp8xx_reg_sc* axp8xx_reg_attach (int /*<<< orphan*/ ,scalar_t__,struct axp8xx_regdef*) ; 
 int /*<<< orphan*/  axp8xx_shutdown ; 
 int /*<<< orphan*/  axp8xx_spec ; 
 int /*<<< orphan*/  axp8xx_sysctl ; 
 int /*<<< orphan*/  axp8xx_sysctl_chargecurrent ; 
 int /*<<< orphan*/  axp8xx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct axp8xx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 struct axp8xx_reg_sc** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nitems (struct axp8xx_regdef*) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static int
axp8xx_attach(device_t dev)
{
	struct axp8xx_softc *sc;
	struct axp8xx_reg_sc *reg;
	uint8_t chip_id, val;
	phandle_t rnode, child;
	int error, i;

	sc = device_get_softc(dev);

	sc->addr = iicbus_get_addr(dev);
	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	error = bus_alloc_resources(dev, axp8xx_spec, &sc->res);
	if (error != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (error);
	}

	if (bootverbose) {
		axp8xx_read(dev, AXP_ICTYPE, &chip_id, 1);
		device_printf(dev, "chip ID 0x%02x\n", chip_id);
	}

	sc->nregs = nitems(axp8xx_common_regdefs);
	sc->type = ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	switch (sc->type) {
	case AXP803:
		sc->nregs += nitems(axp803_regdefs);
		break;
	case AXP813:
		sc->nregs += nitems(axp813_regdefs);
		break;
	}
	sc->config = &axp803_config;
	sc->sensors = axp8xx_common_sensors;
	sc->nsensors = nitems(axp8xx_common_sensors);

	sc->regs = malloc(sizeof(struct axp8xx_reg_sc *) * sc->nregs,
	    M_AXP8XX_REG, M_WAITOK | M_ZERO);

	/* Attach known regulators that exist in the DT */
	rnode = ofw_bus_find_child(ofw_bus_get_node(dev), "regulators");
	if (rnode > 0) {
		for (i = 0; i < sc->nregs; i++) {
			char *regname;
			struct axp8xx_regdef *regdef;

			if (i <= nitems(axp8xx_common_regdefs)) {
				regname = axp8xx_common_regdefs[i].name;
				regdef = &axp8xx_common_regdefs[i];
			} else {
				int off;

				off = i - nitems(axp8xx_common_regdefs);
				switch (sc->type) {
				case AXP803:
					regname = axp803_regdefs[off].name;
					regdef = &axp803_regdefs[off];
					break;
				case AXP813:
					regname = axp813_regdefs[off].name;
					regdef = &axp813_regdefs[off];
					break;
				}
			}
			child = ofw_bus_find_child(rnode,
			    regname);
			if (child == 0)
				continue;
			reg = axp8xx_reg_attach(dev, child,
			    regdef);
			if (reg == NULL) {
				device_printf(dev,
				    "cannot attach regulator %s\n",
				    regname);
				continue;
			}
			sc->regs[i] = reg;
		}
	}

	/* Add sensors */
	for (i = 0; i < sc->nsensors; i++) {
		SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
		    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		    OID_AUTO, sc->sensors[i].name,
		    CTLTYPE_INT | CTLFLAG_RD,
		    dev, sc->sensors[i].id, axp8xx_sysctl,
		    sc->sensors[i].format,
		    sc->sensors[i].desc);
	}
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "batchargecurrentstep",
	    CTLTYPE_INT | CTLFLAG_RW,
	    dev, 0, axp8xx_sysctl_chargecurrent,
	    "I", "Battery Charging Current Step, "
	    "0: 200mA, 1: 400mA, 2: 600mA, 3: 800mA, "
	    "4: 1000mA, 5: 1200mA, 6: 1400mA, 7: 1600mA, "
	    "8: 1800mA, 9: 2000mA, 10: 2200mA, 11: 2400mA, "
	    "12: 2600mA, 13: 2800mA");

	/* Get thresholds */
	if (axp8xx_read(dev, AXP_BAT_CAP_WARN, &val, 1) == 0) {
		sc->warn_thres = (val & AXP_BAT_CAP_WARN_LV1) >> 4;
		sc->warn_thres += AXP_BAP_CAP_WARN_LV1BASE;
		sc->shut_thres = (val & AXP_BAT_CAP_WARN_LV2);
		if (bootverbose) {
			device_printf(dev,
			    "Raw reg val: 0x%02x\n", val);
			device_printf(dev,
			    "Warning threshold: 0x%02x\n", sc->warn_thres);
			device_printf(dev,
			    "Shutdown threshold: 0x%02x\n", sc->shut_thres);
		}
	}

	/* Enable interrupts */
	axp8xx_write(dev, AXP_IRQEN1,
	    AXP_IRQEN1_VBUS_LO |
	    AXP_IRQEN1_VBUS_HI |
	    AXP_IRQEN1_ACIN_LO |
	    AXP_IRQEN1_ACIN_HI);
	axp8xx_write(dev, AXP_IRQEN2,
	    AXP_IRQEN2_BATCHGD |
	    AXP_IRQEN2_BATCHGC |
	    AXP_IRQEN2_BAT_NO |
	    AXP_IRQEN2_BAT_IN);
	axp8xx_write(dev, AXP_IRQEN3, 0);
	axp8xx_write(dev, AXP_IRQEN4,
	    AXP_IRQEN4_BATLVL_LO0 |
	    AXP_IRQEN4_BATLVL_LO1);
	axp8xx_write(dev, AXP_IRQEN5,
	    AXP_IRQEN5_POKSIRQ |
	    AXP_IRQEN5_POKLIRQ);
	axp8xx_write(dev, AXP_IRQEN6, 0);

	/* Install interrupt handler */
	error = bus_setup_intr(dev, sc->res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, axp8xx_intr, dev, &sc->ih);
	if (error != 0) {
		device_printf(dev, "cannot setup interrupt handler\n");
		return (error);
	}

	EVENTHANDLER_REGISTER(shutdown_final, axp8xx_shutdown, dev,
	    SHUTDOWN_PRI_LAST);

	sc->gpiodev = gpiobus_attach_bus(dev);

	return (0);
}