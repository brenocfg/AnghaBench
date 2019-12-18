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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fsl_pcib_softc {int sc_rid; int sc_ip_min; int sc_ip_maj; int sc_pcie; int sc_pcie_capreg; int /*<<< orphan*/ * sc_ih; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_cfg_mtx; int /*<<< orphan*/ * sc_res; scalar_t__ sc_busnr; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int IP_MJ_M ; 
 int IP_MJ_S ; 
 int IP_MN_M ; 
 int IP_MN_S ; 
 int LTSSM_STAT_L0 ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int PCIB_BCR_SECBUS_RESET ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int PCIM_CMD_SERRESPEN ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int PCIR_CAP_PTR ; 
 int PCIR_COMMAND ; 
 int PCIR_LTSSM ; 
 int PCIR_VENDOR ; 
#define  PCIY_EXPRESS 129 
#define  PCIY_PCIX 128 
 int /*<<< orphan*/  REG_PEX_IP_BLK_REV1 ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 struct fsl_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 void* fsl_pcib_cfgread (struct fsl_pcib_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fsl_pcib_cfgwrite (struct fsl_pcib_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ fsl_pcib_decode_win (int /*<<< orphan*/ ,struct fsl_pcib_softc*) ; 
 int fsl_pcib_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_pcib_err_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_pcib_err_intr ; 
 int fsl_pcib_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsl_pcib_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_pci_attach (int /*<<< orphan*/ ) ; 
 int ofw_pci_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fsl_pcib_attach(device_t dev)
{
	struct fsl_pcib_softc *sc;
	phandle_t node;
	uint32_t cfgreg, brctl, ipreg;
	int error, rid;
	uint8_t ltssm, capptr;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->sc_rid = 0;
	sc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rid,
	    RF_ACTIVE);
	if (sc->sc_res == NULL) {
		device_printf(dev, "could not map I/O memory\n");
		return (ENXIO);
	}
	sc->sc_bst = rman_get_bustag(sc->sc_res);
	sc->sc_bsh = rman_get_bushandle(sc->sc_res);
	sc->sc_busnr = 0;

	ipreg = bus_read_4(sc->sc_res, REG_PEX_IP_BLK_REV1);
	sc->sc_ip_min = (ipreg & IP_MN_M) >> IP_MN_S;
	sc->sc_ip_maj = (ipreg & IP_MJ_M) >> IP_MJ_S;
	mtx_init(&sc->sc_cfg_mtx, "pcicfg", NULL, MTX_SPIN);

	cfgreg = fsl_pcib_cfgread(sc, 0, 0, 0, PCIR_VENDOR, 2);
	if (cfgreg != 0x1057 && cfgreg != 0x1957)
		goto err;

	capptr = fsl_pcib_cfgread(sc, 0, 0, 0, PCIR_CAP_PTR, 1);
	while (capptr != 0) {
		cfgreg = fsl_pcib_cfgread(sc, 0, 0, 0, capptr, 2);
		switch (cfgreg & 0xff) {
		case PCIY_PCIX:
			break;
		case PCIY_EXPRESS:
			sc->sc_pcie = 1;
			sc->sc_pcie_capreg = capptr;
			break;
		}
		capptr = (cfgreg >> 8) & 0xff;
	}

	node = ofw_bus_get_node(dev);

	/*
	 * Initialize generic OF PCI interface (ranges, etc.)
	 */

	error = ofw_pci_init(dev);
	if (error)
		return (error);

	/*
	 * Configure decode windows for PCI(E) access.
	 */
	if (fsl_pcib_decode_win(node, sc) != 0)
		goto err;

	cfgreg = fsl_pcib_cfgread(sc, 0, 0, 0, PCIR_COMMAND, 2);
	cfgreg |= PCIM_CMD_SERRESPEN | PCIM_CMD_BUSMASTEREN | PCIM_CMD_MEMEN |
	    PCIM_CMD_PORTEN;
	fsl_pcib_cfgwrite(sc, 0, 0, 0, PCIR_COMMAND, cfgreg, 2);

	/* Reset the bus.  Needed for Radeon video cards. */
	brctl = fsl_pcib_read_config(sc->sc_dev, 0, 0, 0,
	    PCIR_BRIDGECTL_1, 1);
	brctl |= PCIB_BCR_SECBUS_RESET;
	fsl_pcib_write_config(sc->sc_dev, 0, 0, 0,
	    PCIR_BRIDGECTL_1, brctl, 1);
	DELAY(100000);
	brctl &= ~PCIB_BCR_SECBUS_RESET;
	fsl_pcib_write_config(sc->sc_dev, 0, 0, 0,
	    PCIR_BRIDGECTL_1, brctl, 1);
	DELAY(100000);

	if (sc->sc_pcie) {
		ltssm = fsl_pcib_cfgread(sc, 0, 0, 0, PCIR_LTSSM, 1);
		if (ltssm < LTSSM_STAT_L0) {
			if (bootverbose)
				printf("PCI %d: no PCIE link, skipping\n",
				    device_get_unit(dev));
			return (0);
		}
	}

	/* Allocate irq */
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_irq_res == NULL) {
		error = fsl_pcib_detach(dev);
		if (error != 0) {
			device_printf(dev,
			    "Detach of the driver failed with error %d\n",
			    error);
		}
		return (ENXIO);
	}

	/* Setup interrupt handler */
	error = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, fsl_pcib_err_intr, dev, &sc->sc_ih);
	if (error != 0) {
		device_printf(dev, "Could not setup irq, %d\n", error);
		sc->sc_ih = NULL;
		error = fsl_pcib_detach(dev);
		if (error != 0) {
			device_printf(dev,
			    "Detach of the driver failed with error %d\n",
			    error);
		}
		return (ENXIO);
	}

	fsl_pcib_err_init(dev);

	return (ofw_pci_attach(dev));

err:
	return (ENXIO);
}