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
struct msk_softc {scalar_t__ msk_res_spec; scalar_t__ msk_irq_spec; int msk_hw_id; int msk_hw_rev; int msk_pmd; int msk_num_port; int msk_expcap; int msk_pcixcap; int msk_clock; int msk_pflags; int msk_intrmask; int msk_intrhwemask; int /*<<< orphan*/  msk_intrhand; int /*<<< orphan*/ * msk_irq; int /*<<< orphan*/ ** msk_devs; int /*<<< orphan*/  msk_bustype; int /*<<< orphan*/  msk_dev; void* msk_int_holdoff; void* msk_process_limit; int /*<<< orphan*/  msk_mtx; int /*<<< orphan*/ * msk_res; } ;
struct msk_mii_data {size_t port; int pmd; int mii_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B2_CHIP_ID ; 
 int /*<<< orphan*/  B2_MAC_CFG ; 
 int /*<<< orphan*/  B2_PMD_TYP ; 
 int /*<<< orphan*/  B2_Y2_CLK_GATE ; 
 int /*<<< orphan*/  B2_Y2_HW_RES ; 
 int CFG_DUAL_MAC_MSK ; 
#define  CHIP_ID_YUKON_EC 136 
#define  CHIP_ID_YUKON_EC_U 135 
#define  CHIP_ID_YUKON_EX 134 
#define  CHIP_ID_YUKON_FE 133 
#define  CHIP_ID_YUKON_FE_P 132 
#define  CHIP_ID_YUKON_OPT 131 
#define  CHIP_ID_YUKON_SUPR 130 
#define  CHIP_ID_YUKON_UL_2 129 
 int CHIP_ID_YUKON_UNKNOWN ; 
#define  CHIP_ID_YUKON_XL 128 
 int CHIP_REV_YU_EX_A0 ; 
 int CHIP_REV_YU_EX_B0 ; 
 int CHIP_REV_YU_FE_P_A0 ; 
 int /*<<< orphan*/  CSR_PCI_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSR_READ_1 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_RST_CLR ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int MIIF_DOPAUSE ; 
 int MIIF_HAVEFIBER ; 
 int MIIF_MACPRIV0 ; 
 int MSK_FLAG_AUTOTX_CSUM ; 
 int MSK_FLAG_DESCV2 ; 
 int MSK_FLAG_FASTETHER ; 
 int MSK_FLAG_JUMBO ; 
 int MSK_FLAG_JUMBO_NOCSUM ; 
 int MSK_FLAG_MSI ; 
 int MSK_FLAG_NOHWVLAN ; 
 int MSK_FLAG_NORXCHK ; 
 int MSK_FLAG_NORX_CSUM ; 
 void* MSK_INT_HOLDOFF_DEFAULT ; 
 int /*<<< orphan*/  MSK_PCIX_BUS ; 
 int /*<<< orphan*/  MSK_PCI_BUS ; 
 int /*<<< orphan*/  MSK_PEX_BUS ; 
 size_t MSK_PORT_A ; 
 size_t MSK_PORT_B ; 
 void* MSK_PROC_DEFAULT ; 
 void* MSK_PROC_MAX ; 
 void* MSK_PROC_MIN ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  PCIY_PCIX ; 
 int /*<<< orphan*/  PCI_OUR_REG_3 ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int Y2_IS_HW_ERR ; 
 int Y2_IS_IRQ_STAT ; 
 int Y2_IS_MST_ERR ; 
 int Y2_IS_PCI_EXP ; 
 int Y2_IS_PCI_NEXP ; 
 int Y2_IS_STAT_BMU ; 
 int Y2_IS_TIST_OV ; 
 int Y2_STATUS_LNK2_INAC ; 
 scalar_t__ bootverbose ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct msk_softc*,int /*<<< orphan*/ *) ; 
 void* device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct msk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct msk_mii_data*) ; 
 scalar_t__ legacy_intr ; 
 struct msk_mii_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int msi_disable ; 
 int /*<<< orphan*/  msk_intr ; 
 scalar_t__ msk_irq_spec_legacy ; 
 scalar_t__ msk_irq_spec_msi ; 
 void* msk_res_spec_io ; 
 scalar_t__ msk_res_spec_mem ; 
 int msk_status_dma_alloc (struct msk_softc*) ; 
 int /*<<< orphan*/  mskc_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mskc_reset (struct msk_softc*) ; 
 int mskc_setup_rambuffer (struct msk_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  sysctl_hw_msk_proc_limit ; 

__attribute__((used)) static int
mskc_attach(device_t dev)
{
	struct msk_softc *sc;
	struct msk_mii_data *mmd;
	int error, msic, msir, reg;

	sc = device_get_softc(dev);
	sc->msk_dev = dev;
	mtx_init(&sc->msk_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	/* Allocate I/O resource */
#ifdef MSK_USEIOSPACE
	sc->msk_res_spec = msk_res_spec_io;
#else
	sc->msk_res_spec = msk_res_spec_mem;
#endif
	sc->msk_irq_spec = msk_irq_spec_legacy;
	error = bus_alloc_resources(dev, sc->msk_res_spec, sc->msk_res);
	if (error) {
		if (sc->msk_res_spec == msk_res_spec_mem)
			sc->msk_res_spec = msk_res_spec_io;
		else
			sc->msk_res_spec = msk_res_spec_mem;
		error = bus_alloc_resources(dev, sc->msk_res_spec, sc->msk_res);
		if (error) {
			device_printf(dev, "couldn't allocate %s resources\n",
			    sc->msk_res_spec == msk_res_spec_mem ? "memory" :
			    "I/O");
			mtx_destroy(&sc->msk_mtx);
			return (ENXIO);
		}
	}

	/* Enable all clocks before accessing any registers. */
	CSR_PCI_WRITE_4(sc, PCI_OUR_REG_3, 0);

	CSR_WRITE_2(sc, B0_CTST, CS_RST_CLR);
	sc->msk_hw_id = CSR_READ_1(sc, B2_CHIP_ID);
	sc->msk_hw_rev = (CSR_READ_1(sc, B2_MAC_CFG) >> 4) & 0x0f;
	/* Bail out if chip is not recognized. */
	if (sc->msk_hw_id < CHIP_ID_YUKON_XL ||
	    sc->msk_hw_id > CHIP_ID_YUKON_OPT ||
	    sc->msk_hw_id == CHIP_ID_YUKON_UNKNOWN) {
		device_printf(dev, "unknown device: id=0x%02x, rev=0x%02x\n",
		    sc->msk_hw_id, sc->msk_hw_rev);
		mtx_destroy(&sc->msk_mtx);
		return (ENXIO);
	}

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "process_limit", CTLTYPE_INT | CTLFLAG_RW,
	    &sc->msk_process_limit, 0, sysctl_hw_msk_proc_limit, "I",
	    "max number of Rx events to process");

	sc->msk_process_limit = MSK_PROC_DEFAULT;
	error = resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "process_limit", &sc->msk_process_limit);
	if (error == 0) {
		if (sc->msk_process_limit < MSK_PROC_MIN ||
		    sc->msk_process_limit > MSK_PROC_MAX) {
			device_printf(dev, "process_limit value out of range; "
			    "using default: %d\n", MSK_PROC_DEFAULT);
			sc->msk_process_limit = MSK_PROC_DEFAULT;
		}
	}

	sc->msk_int_holdoff = MSK_INT_HOLDOFF_DEFAULT;
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "int_holdoff", CTLFLAG_RW, &sc->msk_int_holdoff, 0,
	    "Maximum number of time to delay interrupts");
	resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "int_holdoff", &sc->msk_int_holdoff);

	sc->msk_pmd = CSR_READ_1(sc, B2_PMD_TYP);
	/* Check number of MACs. */
	sc->msk_num_port = 1;
	if ((CSR_READ_1(sc, B2_Y2_HW_RES) & CFG_DUAL_MAC_MSK) ==
	    CFG_DUAL_MAC_MSK) {
		if (!(CSR_READ_1(sc, B2_Y2_CLK_GATE) & Y2_STATUS_LNK2_INAC))
			sc->msk_num_port++;
	}

	/* Check bus type. */
	if (pci_find_cap(sc->msk_dev, PCIY_EXPRESS, &reg) == 0) {
		sc->msk_bustype = MSK_PEX_BUS;
		sc->msk_expcap = reg;
	} else if (pci_find_cap(sc->msk_dev, PCIY_PCIX, &reg) == 0) {
		sc->msk_bustype = MSK_PCIX_BUS;
		sc->msk_pcixcap = reg;
	} else
		sc->msk_bustype = MSK_PCI_BUS;

	switch (sc->msk_hw_id) {
	case CHIP_ID_YUKON_EC:
		sc->msk_clock = 125;	/* 125 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO;
		break;
	case CHIP_ID_YUKON_EC_U:
		sc->msk_clock = 125;	/* 125 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO | MSK_FLAG_JUMBO_NOCSUM;
		break;
	case CHIP_ID_YUKON_EX:
		sc->msk_clock = 125;	/* 125 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO | MSK_FLAG_DESCV2 |
		    MSK_FLAG_AUTOTX_CSUM;
		/*
		 * Yukon Extreme seems to have silicon bug for
		 * automatic Tx checksum calculation capability.
		 */
		if (sc->msk_hw_rev == CHIP_REV_YU_EX_B0)
			sc->msk_pflags &= ~MSK_FLAG_AUTOTX_CSUM;
		/*
		 * Yukon Extreme A0 could not use store-and-forward
		 * for jumbo frames, so disable Tx checksum
		 * offloading for jumbo frames.
		 */
		if (sc->msk_hw_rev == CHIP_REV_YU_EX_A0)
			sc->msk_pflags |= MSK_FLAG_JUMBO_NOCSUM;
		break;
	case CHIP_ID_YUKON_FE:
		sc->msk_clock = 100;	/* 100 MHz */
		sc->msk_pflags |= MSK_FLAG_FASTETHER;
		break;
	case CHIP_ID_YUKON_FE_P:
		sc->msk_clock = 50;	/* 50 MHz */
		sc->msk_pflags |= MSK_FLAG_FASTETHER | MSK_FLAG_DESCV2 |
		    MSK_FLAG_AUTOTX_CSUM;
		if (sc->msk_hw_rev == CHIP_REV_YU_FE_P_A0) {
			/*
			 * XXX
			 * FE+ A0 has status LE writeback bug so msk(4)
			 * does not rely on status word of received frame
			 * in msk_rxeof() which in turn disables all
			 * hardware assistance bits reported by the status
			 * word as well as validity of the received frame.
			 * Just pass received frames to upper stack with
			 * minimal test and let upper stack handle them.
			 */
			sc->msk_pflags |= MSK_FLAG_NOHWVLAN |
			    MSK_FLAG_NORXCHK | MSK_FLAG_NORX_CSUM;
		}
		break;
	case CHIP_ID_YUKON_XL:
		sc->msk_clock = 156;	/* 156 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO;
		break;
	case CHIP_ID_YUKON_SUPR:
		sc->msk_clock = 125;	/* 125 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO | MSK_FLAG_DESCV2 |
		    MSK_FLAG_AUTOTX_CSUM;
		break;
	case CHIP_ID_YUKON_UL_2:
		sc->msk_clock = 125;	/* 125 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO;
		break;
	case CHIP_ID_YUKON_OPT:
		sc->msk_clock = 125;	/* 125 MHz */
		sc->msk_pflags |= MSK_FLAG_JUMBO | MSK_FLAG_DESCV2;
		break;
	default:
		sc->msk_clock = 156;	/* 156 MHz */
		break;
	}

	/* Allocate IRQ resources. */
	msic = pci_msi_count(dev);
	if (bootverbose)
		device_printf(dev, "MSI count : %d\n", msic);
	if (legacy_intr != 0)
		msi_disable = 1;
	if (msi_disable == 0 && msic > 0) {
		msir = 1;
		if (pci_alloc_msi(dev, &msir) == 0) {
			if (msir == 1) {
				sc->msk_pflags |= MSK_FLAG_MSI;
				sc->msk_irq_spec = msk_irq_spec_msi;
			} else
				pci_release_msi(dev);
		}
	}

	error = bus_alloc_resources(dev, sc->msk_irq_spec, sc->msk_irq);
	if (error) {
		device_printf(dev, "couldn't allocate IRQ resources\n");
		goto fail;
	}

	if ((error = msk_status_dma_alloc(sc)) != 0)
		goto fail;

	/* Set base interrupt mask. */
	sc->msk_intrmask = Y2_IS_HW_ERR | Y2_IS_STAT_BMU;
	sc->msk_intrhwemask = Y2_IS_TIST_OV | Y2_IS_MST_ERR |
	    Y2_IS_IRQ_STAT | Y2_IS_PCI_EXP | Y2_IS_PCI_NEXP;

	/* Reset the adapter. */
	mskc_reset(sc);

	if ((error = mskc_setup_rambuffer(sc)) != 0)
		goto fail;

	sc->msk_devs[MSK_PORT_A] = device_add_child(dev, "msk", -1);
	if (sc->msk_devs[MSK_PORT_A] == NULL) {
		device_printf(dev, "failed to add child for PORT_A\n");
		error = ENXIO;
		goto fail;
	}
	mmd = malloc(sizeof(struct msk_mii_data), M_DEVBUF, M_WAITOK | M_ZERO);
	mmd->port = MSK_PORT_A;
	mmd->pmd = sc->msk_pmd;
	mmd->mii_flags |= MIIF_DOPAUSE;
	if (sc->msk_pmd == 'L' || sc->msk_pmd == 'S')
		mmd->mii_flags |= MIIF_HAVEFIBER;
	if (sc->msk_pmd == 'P')
		mmd->mii_flags |= MIIF_HAVEFIBER | MIIF_MACPRIV0;
	device_set_ivars(sc->msk_devs[MSK_PORT_A], mmd);

	if (sc->msk_num_port > 1) {
		sc->msk_devs[MSK_PORT_B] = device_add_child(dev, "msk", -1);
		if (sc->msk_devs[MSK_PORT_B] == NULL) {
			device_printf(dev, "failed to add child for PORT_B\n");
			error = ENXIO;
			goto fail;
		}
		mmd = malloc(sizeof(struct msk_mii_data), M_DEVBUF, M_WAITOK |
		    M_ZERO);
		mmd->port = MSK_PORT_B;
		mmd->pmd = sc->msk_pmd;
		if (sc->msk_pmd == 'L' || sc->msk_pmd == 'S')
			mmd->mii_flags |= MIIF_HAVEFIBER;
		if (sc->msk_pmd == 'P')
			mmd->mii_flags |= MIIF_HAVEFIBER | MIIF_MACPRIV0;
		device_set_ivars(sc->msk_devs[MSK_PORT_B], mmd);
	}

	error = bus_generic_attach(dev);
	if (error) {
		device_printf(dev, "failed to attach port(s)\n");
		goto fail;
	}

	/* Hook interrupt last to avoid having to lock softc. */
	error = bus_setup_intr(dev, sc->msk_irq[0], INTR_TYPE_NET |
	    INTR_MPSAFE, NULL, msk_intr, sc, &sc->msk_intrhand);
	if (error != 0) {
		device_printf(dev, "couldn't set up interrupt handler\n");
		goto fail;
	}
fail:
	if (error != 0)
		mskc_detach(dev);

	return (error);
}