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
struct cqspi_softc {int fifo_depth; void* trigger_address; void* fifo_width; int /*<<< orphan*/  dev; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;

/* Variables and functions */
 int CFG_BAUD12 ; 
 int CFG_BAUD_M ; 
 int CFG_EN ; 
 int CFG_ENDMA ; 
 int /*<<< orphan*/  CQSPI_CFG ; 
 int /*<<< orphan*/  CQSPI_DELAY ; 
 int /*<<< orphan*/  CQSPI_DEVSZ ; 
 int /*<<< orphan*/  CQSPI_MODULEID ; 
 int /*<<< orphan*/  CQSPI_RDDATACAP ; 
 int /*<<< orphan*/  CQSPI_SRAMPART ; 
 int DELAY_AFTER_S ; 
 int DELAY_BTWN_S ; 
 int DELAY_INIT_S ; 
 int DELAY_NSS_S ; 
 int DEVSZ_NUMADDRBYTES_M ; 
 int DEVSZ_NUMADDRBYTES_S ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,void**,int) ; 
 int OF_getproplen (int,char*) ; 
 int RDDATACAP_DELAY_M ; 
 int RDDATACAP_DELAY_S ; 
 int READ4 (struct cqspi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct cqspi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cqspi_init(struct cqspi_softc *sc)
{
	pcell_t dts_value[1];
	phandle_t node;
	uint32_t reg;
	int len;

	device_printf(sc->dev, "Module ID %x\n",
	    READ4(sc, CQSPI_MODULEID));

	if ((node = ofw_bus_get_node(sc->dev)) == -1) {
		return (ENXIO);
	}

	if ((len = OF_getproplen(node, "cdns,fifo-depth")) <= 0) {
		return (ENXIO);
	}
	OF_getencprop(node, "cdns,fifo-depth", dts_value, len);
	sc->fifo_depth = dts_value[0];

	if ((len = OF_getproplen(node, "cdns,fifo-width")) <= 0) {
		return (ENXIO);
	}
	OF_getencprop(node, "cdns,fifo-width", dts_value, len);
	sc->fifo_width = dts_value[0];

	if ((len = OF_getproplen(node, "cdns,trigger-address")) <= 0) {
		return (ENXIO);
	}
	OF_getencprop(node, "cdns,trigger-address", dts_value, len);
	sc->trigger_address = dts_value[0];

	/* Disable controller */
	reg = READ4(sc, CQSPI_CFG);
	reg &= ~(CFG_EN);
	WRITE4(sc, CQSPI_CFG, reg);

	reg = READ4(sc, CQSPI_DEVSZ);
	reg &= ~(DEVSZ_NUMADDRBYTES_M);
	reg |= ((4 - 1) - DEVSZ_NUMADDRBYTES_S);
	WRITE4(sc, CQSPI_DEVSZ, reg);

	WRITE4(sc, CQSPI_SRAMPART, sc->fifo_depth/2);

	/* TODO: calculate baud rate and delay values. */

	reg = READ4(sc, CQSPI_CFG);
	/* Configure baud rate */
	reg &= ~(CFG_BAUD_M);
	reg |= CFG_BAUD12;
	reg |= CFG_ENDMA;
	WRITE4(sc, CQSPI_CFG, reg);

	reg = (3 << DELAY_NSS_S);
	reg |= (3  << DELAY_BTWN_S);
	reg |= (1 << DELAY_AFTER_S);
	reg |= (1 << DELAY_INIT_S);
	WRITE4(sc, CQSPI_DELAY, reg);

	READ4(sc, CQSPI_RDDATACAP);
	reg &= ~(RDDATACAP_DELAY_M);
	reg |= (1 << RDDATACAP_DELAY_S);
	WRITE4(sc, CQSPI_RDDATACAP, reg);

	/* Enable controller */
	reg = READ4(sc, CQSPI_CFG);
	reg |= (CFG_EN);
	WRITE4(sc, CQSPI_CFG, reg);

	return (0);
}