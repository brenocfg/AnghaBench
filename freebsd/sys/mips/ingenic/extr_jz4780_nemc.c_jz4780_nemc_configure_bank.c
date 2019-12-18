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
typedef  int /*<<< orphan*/  val ;
typedef  int uint32_t ;
typedef  int u_int ;
struct jz4780_nemc_softc {int banks; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_4 (struct jz4780_nemc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_nemc_softc*,int /*<<< orphan*/ ,int) ; 
 int JZ4780_NEMC_NS_TO_TICKS (struct jz4780_nemc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_NEMC_SMCR (int) ; 
 int JZ_NEMC_SMCR_SMT_MASK ; 
 int JZ_NEMC_SMCR_SMT_NORMAL ; 
 int JZ_NEMC_SMCR_SMT_SHIFT ; 
 int JZ_NEMC_SMCR_STRV_MASK ; 
 int JZ_NEMC_SMCR_STRV_SHIFT ; 
 int JZ_NEMC_SMCR_TAH_MASK ; 
 int JZ_NEMC_SMCR_TAH_SHIFT ; 
 int JZ_NEMC_SMCR_TAS_MASK ; 
 int JZ_NEMC_SMCR_TAS_SHIFT ; 
 int JZ_NEMC_SMCR_TAW_MASK ; 
 int JZ_NEMC_SMCR_TAW_SHIFT ; 
 int JZ_NEMC_SMCR_TBP_MASK ; 
 int JZ_NEMC_SMCR_TBP_SHIFT ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int* ticks_to_tBP_tAW ; 

__attribute__((used)) static int
jz4780_nemc_configure_bank(struct jz4780_nemc_softc *sc,
        device_t dev, u_int bank)
{
	uint32_t smcr, cycles;
	phandle_t node;
	pcell_t   val;

	/* Check if bank is configured already */
	if (sc->banks & (1 << bank))
		return 0;

	smcr = CSR_READ_4(sc, JZ_NEMC_SMCR(bank));

	smcr &= ~JZ_NEMC_SMCR_SMT_MASK;
	smcr |= JZ_NEMC_SMCR_SMT_NORMAL << JZ_NEMC_SMCR_SMT_SHIFT;

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "ingenic,nemc-tAS", &val, sizeof(val)) > 0) {
		cycles = JZ4780_NEMC_NS_TO_TICKS(sc, val);
		if (cycles > 15) {
			device_printf(sc->dev,
			    "invalid value of %s %u (%u cycles), maximum %u cycles supported\n",
			    "ingenic,nemc-tAS", val, cycles, 15);
			return -1;
		}
		smcr &= ~JZ_NEMC_SMCR_TAS_MASK;
		smcr |= cycles << JZ_NEMC_SMCR_TAS_SHIFT;
	}

	if (OF_getencprop(node, "ingenic,nemc-tAH", &val, sizeof(val)) > 0) {
		cycles = JZ4780_NEMC_NS_TO_TICKS(sc, val);
		if (cycles > 15) {
			device_printf(sc->dev,
			    "invalid value of %s %u (%u cycles), maximum %u cycles supported\n",
			    "ingenic,nemc-tAH", val, cycles, 15);
			return -1;
		}
		smcr &= ~JZ_NEMC_SMCR_TAH_MASK;
		smcr |= cycles << JZ_NEMC_SMCR_TAH_SHIFT;
	}

	if (OF_getencprop(node, "ingenic,nemc-tBP", &val, sizeof(val)) > 0) {
		cycles = JZ4780_NEMC_NS_TO_TICKS(sc, val);
		if (cycles > 31) {
			device_printf(sc->dev,
			    "invalid value of %s %u (%u cycles), maximum %u cycles supported\n",
			    "ingenic,nemc-tBP", val, cycles, 15);
			return -1;
		}
		smcr &= ~JZ_NEMC_SMCR_TBP_MASK;
		smcr |= ticks_to_tBP_tAW[cycles] << JZ_NEMC_SMCR_TBP_SHIFT;
	}

	if (OF_getencprop(node, "ingenic,nemc-tAW", &val, sizeof(val)) > 0) {
		cycles = JZ4780_NEMC_NS_TO_TICKS(sc, val);
		if (cycles > 31) {
			device_printf(sc->dev,
			    "invalid value of %s %u (%u cycles), maximum %u cycles supported\n",
			    "ingenic,nemc-tAW", val, cycles, 15);
			return -1;
		}
		smcr &= ~JZ_NEMC_SMCR_TAW_MASK;
		smcr |= ticks_to_tBP_tAW[cycles] << JZ_NEMC_SMCR_TAW_SHIFT;
	}

	if (OF_getencprop(node, "ingenic,nemc-tSTRV", &val, sizeof(val)) > 0) {
		cycles = JZ4780_NEMC_NS_TO_TICKS(sc, val);
		if (cycles > 63) {
			device_printf(sc->dev,
			    "invalid value of %s %u (%u cycles), maximum %u cycles supported\n",
			    "ingenic,nemc-tSTRV", val, cycles, 15);
			return -1;
		}
		smcr &= ~JZ_NEMC_SMCR_STRV_MASK;
		smcr |= cycles << JZ_NEMC_SMCR_STRV_SHIFT;
	}
	CSR_WRITE_4(sc, JZ_NEMC_SMCR(bank), smcr);
	sc->banks |= (1 << bank);
	return 0;
}