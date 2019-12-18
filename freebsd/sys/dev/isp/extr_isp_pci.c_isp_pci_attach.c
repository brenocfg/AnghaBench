#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_21__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct isp_spi {int dummy; } ;
struct TYPE_32__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_33__ {TYPE_2__ pc; TYPE_21__* fw; } ;
struct TYPE_34__ {int isp_nchan; int isp_revision; int isp_nirq; int /*<<< orphan*/  isp_lock; TYPE_3__ isp_osinfo; int /*<<< orphan*/ * isp_param; int /*<<< orphan*/  isp_port; TYPE_5__* isp_mdvec; int /*<<< orphan*/ * isp_regs2; int /*<<< orphan*/ * isp_regs; void* isp_type; void* isp_dev; } ;
struct isp_pcisoftc {scalar_t__ rgd; scalar_t__ rtp; scalar_t__ rtp1; scalar_t__ rgd1; scalar_t__ rtp2; scalar_t__ rgd2; TYPE_4__ pci_isp; int /*<<< orphan*/ * regs2; int /*<<< orphan*/ * regs1; int /*<<< orphan*/ * regs; scalar_t__ msicount; TYPE_1__* irq; void** pci_poff; void* pci_dev; } ;
struct isp_fc {int dummy; } ;
typedef  int /*<<< orphan*/  sdparam ;
typedef  TYPE_4__ ispsoftc_t ;
typedef  int /*<<< orphan*/  fwname ;
typedef  int /*<<< orphan*/  fcparam ;
typedef  void* device_t ;
struct TYPE_35__ {int /*<<< orphan*/  dv_ispfw; } ;
struct TYPE_31__ {int /*<<< orphan*/  data; } ;
struct TYPE_30__ {scalar_t__ iqd; int /*<<< orphan*/ * irq; int /*<<< orphan*/  ih; } ;

/* Variables and functions */
 size_t BIU_BLOCK ; 
 void* BIU_REGS_OFF ; 
 size_t DMA_BLOCK ; 
 void* DMA_REGS_OFF ; 
 int ENXIO ; 
 void* ISP1080_DMA_REGS_OFF ; 
 void* ISP_HA_FC_2100 ; 
 void* ISP_HA_FC_2200 ; 
 void* ISP_HA_FC_2300 ; 
 void* ISP_HA_FC_2312 ; 
 void* ISP_HA_FC_2322 ; 
 void* ISP_HA_FC_2400 ; 
 void* ISP_HA_FC_2500 ; 
 void* ISP_HA_FC_2600 ; 
 void* ISP_HA_FC_2700 ; 
 void* ISP_HA_SCSI_10160 ; 
 void* ISP_HA_SCSI_1080 ; 
 void* ISP_HA_SCSI_12160 ; 
 void* ISP_HA_SCSI_1240 ; 
 void* ISP_HA_SCSI_1280 ; 
 void* ISP_HA_SCSI_UNKNOWN ; 
 int /*<<< orphan*/  ISP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  ISP_LOGCONFIG ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 int /*<<< orphan*/  ISP_LOGWARN ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_4__*) ; 
 scalar_t__ IS_2300 (TYPE_4__*) ; 
 scalar_t__ IS_2322 (TYPE_4__*) ; 
 scalar_t__ IS_23XX (TYPE_4__*) ; 
 scalar_t__ IS_24XX (TYPE_4__*) ; 
 scalar_t__ IS_26XX (TYPE_4__*) ; 
 scalar_t__ IS_FC (TYPE_4__*) ; 
 size_t MBOX_BLOCK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_INTX_DISABLE ; 
 int PCIM_CMD_INVEN ; 
 int PCIM_CMD_PERRESPEN ; 
 int PCIM_CMD_SEREN ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  PCIR_ROMADDR ; 
 int PCI_DFLT_LNSZ ; 
 int PCI_DFLT_LTNCY ; 
 void* PCI_MBOX_REGS2100_OFF ; 
 void* PCI_MBOX_REGS2300_OFF ; 
 void* PCI_MBOX_REGS2400_OFF ; 
 void* PCI_MBOX_REGS_OFF ; 
#define  PCI_QLOGIC_ISP10160 150 
#define  PCI_QLOGIC_ISP1020 149 
#define  PCI_QLOGIC_ISP1080 148 
#define  PCI_QLOGIC_ISP12160 147 
#define  PCI_QLOGIC_ISP1240 146 
#define  PCI_QLOGIC_ISP1280 145 
#define  PCI_QLOGIC_ISP2031 144 
#define  PCI_QLOGIC_ISP2100 143 
#define  PCI_QLOGIC_ISP2200 142 
#define  PCI_QLOGIC_ISP2300 141 
#define  PCI_QLOGIC_ISP2312 140 
#define  PCI_QLOGIC_ISP2322 139 
#define  PCI_QLOGIC_ISP2422 138 
#define  PCI_QLOGIC_ISP2432 137 
#define  PCI_QLOGIC_ISP2532 136 
#define  PCI_QLOGIC_ISP2684 135 
#define  PCI_QLOGIC_ISP2692 134 
#define  PCI_QLOGIC_ISP2714 133 
#define  PCI_QLOGIC_ISP2722 132 
#define  PCI_QLOGIC_ISP5432 131 
#define  PCI_QLOGIC_ISP6312 130 
#define  PCI_QLOGIC_ISP6322 129 
#define  PCI_QLOGIC_ISP8031 128 
 void* PCI_RISC_REGS_OFF ; 
 void* PCI_SXP_REGS_OFF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 size_t RISC_BLOCK ; 
 size_t SXP_BLOCK ; 
 scalar_t__ SYS_RES_IOPORT ; 
 scalar_t__ SYS_RES_IRQ ; 
 void* SYS_RES_MEMORY ; 
 size_t _BLK_REG_SHFT ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (void*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (void*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct isp_pcisoftc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 TYPE_21__* firmware_get (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isp_attach (TYPE_4__*) ; 
 int /*<<< orphan*/  isp_get_generic_options (void*,TYPE_4__*) ; 
 int /*<<< orphan*/  isp_get_specific_options (void*,int,TYPE_4__*) ; 
 scalar_t__ isp_nvports ; 
 int /*<<< orphan*/  isp_prt (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isp_reinit (TYPE_4__*,int) ; 
 int /*<<< orphan*/  isp_shutdown (TYPE_4__*) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ mdvec ; 
 TYPE_5__ mdvec_1080 ; 
 TYPE_5__ mdvec_12160 ; 
 TYPE_5__ mdvec_2100 ; 
 TYPE_5__ mdvec_2200 ; 
 TYPE_5__ mdvec_2300 ; 
 TYPE_5__ mdvec_2400 ; 
 TYPE_5__ mdvec_2500 ; 
 TYPE_5__ mdvec_2600 ; 
 TYPE_5__ mdvec_2700 ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int const pci_get_devid (void*) ; 
 int /*<<< orphan*/  pci_get_function (void*) ; 
 int pci_get_revid (void*) ; 
 int pci_read_config (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_release_msi (void*) ; 
 int /*<<< orphan*/  pci_write_config (void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
isp_pci_attach(device_t dev)
{
	struct isp_pcisoftc *pcs = device_get_softc(dev);
	ispsoftc_t *isp = &pcs->pci_isp;
	int i;
	uint32_t data, cmd, linesz, did;
	size_t psize, xsize;
	char fwname[32];

	pcs->pci_dev = dev;
	isp->isp_dev = dev;
	isp->isp_nchan = 1;
	mtx_init(&isp->isp_lock, "isp", NULL, MTX_DEF);

	/*
	 * Get Generic Options
	 */
	isp_nvports = 0;
	isp_get_generic_options(dev, isp);

	linesz = PCI_DFLT_LNSZ;
	pcs->regs = pcs->regs2 = NULL;
	pcs->rgd = pcs->rtp = 0;

	pcs->pci_dev = dev;
	pcs->pci_poff[BIU_BLOCK >> _BLK_REG_SHFT] = BIU_REGS_OFF;
	pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS_OFF;
	pcs->pci_poff[SXP_BLOCK >> _BLK_REG_SHFT] = PCI_SXP_REGS_OFF;
	pcs->pci_poff[RISC_BLOCK >> _BLK_REG_SHFT] = PCI_RISC_REGS_OFF;
	pcs->pci_poff[DMA_BLOCK >> _BLK_REG_SHFT] = DMA_REGS_OFF;

	switch (pci_get_devid(dev)) {
	case PCI_QLOGIC_ISP1020:
		did = 0x1040;
		isp->isp_mdvec = &mdvec;
		isp->isp_type = ISP_HA_SCSI_UNKNOWN;
		break;
	case PCI_QLOGIC_ISP1080:
		did = 0x1080;
		isp->isp_mdvec = &mdvec_1080;
		isp->isp_type = ISP_HA_SCSI_1080;
		pcs->pci_poff[DMA_BLOCK >> _BLK_REG_SHFT] = ISP1080_DMA_REGS_OFF;
		break;
	case PCI_QLOGIC_ISP1240:
		did = 0x1080;
		isp->isp_mdvec = &mdvec_1080;
		isp->isp_type = ISP_HA_SCSI_1240;
		isp->isp_nchan = 2;
		pcs->pci_poff[DMA_BLOCK >> _BLK_REG_SHFT] = ISP1080_DMA_REGS_OFF;
		break;
	case PCI_QLOGIC_ISP1280:
		did = 0x1080;
		isp->isp_mdvec = &mdvec_1080;
		isp->isp_type = ISP_HA_SCSI_1280;
		pcs->pci_poff[DMA_BLOCK >> _BLK_REG_SHFT] = ISP1080_DMA_REGS_OFF;
		break;
	case PCI_QLOGIC_ISP10160:
		did = 0x12160;
		isp->isp_mdvec = &mdvec_12160;
		isp->isp_type = ISP_HA_SCSI_10160;
		pcs->pci_poff[DMA_BLOCK >> _BLK_REG_SHFT] = ISP1080_DMA_REGS_OFF;
		break;
	case PCI_QLOGIC_ISP12160:
		did = 0x12160;
		isp->isp_nchan = 2;
		isp->isp_mdvec = &mdvec_12160;
		isp->isp_type = ISP_HA_SCSI_12160;
		pcs->pci_poff[DMA_BLOCK >> _BLK_REG_SHFT] = ISP1080_DMA_REGS_OFF;
		break;
	case PCI_QLOGIC_ISP2100:
		did = 0x2100;
		isp->isp_mdvec = &mdvec_2100;
		isp->isp_type = ISP_HA_FC_2100;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2100_OFF;
		if (pci_get_revid(dev) < 3) {
			/*
			 * XXX: Need to get the actual revision
			 * XXX: number of the 2100 FB. At any rate,
			 * XXX: lower cache line size for early revision
			 * XXX; boards.
			 */
			linesz = 1;
		}
		break;
	case PCI_QLOGIC_ISP2200:
		did = 0x2200;
		isp->isp_mdvec = &mdvec_2200;
		isp->isp_type = ISP_HA_FC_2200;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2100_OFF;
		break;
	case PCI_QLOGIC_ISP2300:
		did = 0x2300;
		isp->isp_mdvec = &mdvec_2300;
		isp->isp_type = ISP_HA_FC_2300;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2300_OFF;
		break;
	case PCI_QLOGIC_ISP2312:
	case PCI_QLOGIC_ISP6312:
		did = 0x2300;
		isp->isp_mdvec = &mdvec_2300;
		isp->isp_type = ISP_HA_FC_2312;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2300_OFF;
		break;
	case PCI_QLOGIC_ISP2322:
	case PCI_QLOGIC_ISP6322:
		did = 0x2322;
		isp->isp_mdvec = &mdvec_2300;
		isp->isp_type = ISP_HA_FC_2322;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2300_OFF;
		break;
	case PCI_QLOGIC_ISP2422:
	case PCI_QLOGIC_ISP2432:
		did = 0x2400;
		isp->isp_nchan += isp_nvports;
		isp->isp_mdvec = &mdvec_2400;
		isp->isp_type = ISP_HA_FC_2400;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2400_OFF;
		break;
	case PCI_QLOGIC_ISP2532:
		did = 0x2500;
		isp->isp_nchan += isp_nvports;
		isp->isp_mdvec = &mdvec_2500;
		isp->isp_type = ISP_HA_FC_2500;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2400_OFF;
		break;
	case PCI_QLOGIC_ISP5432:
		did = 0x2500;
		isp->isp_mdvec = &mdvec_2500;
		isp->isp_type = ISP_HA_FC_2500;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2400_OFF;
		break;
	case PCI_QLOGIC_ISP2031:
	case PCI_QLOGIC_ISP8031:
		did = 0x2600;
		isp->isp_nchan += isp_nvports;
		isp->isp_mdvec = &mdvec_2600;
		isp->isp_type = ISP_HA_FC_2600;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2400_OFF;
		break;
	case PCI_QLOGIC_ISP2684:
	case PCI_QLOGIC_ISP2692:
	case PCI_QLOGIC_ISP2714:
	case PCI_QLOGIC_ISP2722:
		did = 0x2700;
		isp->isp_nchan += isp_nvports;
		isp->isp_mdvec = &mdvec_2700;
		isp->isp_type = ISP_HA_FC_2700;
		pcs->pci_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = PCI_MBOX_REGS2400_OFF;
		break;
	default:
		device_printf(dev, "unknown device type\n");
		goto bad;
		break;
	}
	isp->isp_revision = pci_get_revid(dev);

	if (IS_26XX(isp)) {
		pcs->rtp = SYS_RES_MEMORY;
		pcs->rgd = PCIR_BAR(0);
		pcs->regs = bus_alloc_resource_any(dev, pcs->rtp, &pcs->rgd,
		    RF_ACTIVE);
		pcs->rtp1 = SYS_RES_MEMORY;
		pcs->rgd1 = PCIR_BAR(2);
		pcs->regs1 = bus_alloc_resource_any(dev, pcs->rtp1, &pcs->rgd1,
		    RF_ACTIVE);
		pcs->rtp2 = SYS_RES_MEMORY;
		pcs->rgd2 = PCIR_BAR(4);
		pcs->regs2 = bus_alloc_resource_any(dev, pcs->rtp2, &pcs->rgd2,
		    RF_ACTIVE);
	} else {
		pcs->rtp = SYS_RES_MEMORY;
		pcs->rgd = PCIR_BAR(1);
		pcs->regs = bus_alloc_resource_any(dev, pcs->rtp, &pcs->rgd,
		    RF_ACTIVE);
		if (pcs->regs == NULL) {
			pcs->rtp = SYS_RES_IOPORT;
			pcs->rgd = PCIR_BAR(0);
			pcs->regs = bus_alloc_resource_any(dev, pcs->rtp,
			    &pcs->rgd, RF_ACTIVE);
		}
	}
	if (pcs->regs == NULL) {
		device_printf(dev, "Unable to map any ports\n");
		goto bad;
	}
	if (bootverbose) {
		device_printf(dev, "Using %s space register mapping\n",
		    (pcs->rtp == SYS_RES_IOPORT)? "I/O" : "Memory");
	}
	isp->isp_regs = pcs->regs;
	isp->isp_regs2 = pcs->regs2;

	if (IS_FC(isp)) {
		psize = sizeof (fcparam);
		xsize = sizeof (struct isp_fc);
	} else {
		psize = sizeof (sdparam);
		xsize = sizeof (struct isp_spi);
	}
	psize *= isp->isp_nchan;
	xsize *= isp->isp_nchan;
	isp->isp_param = malloc(psize, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (isp->isp_param == NULL) {
		device_printf(dev, "cannot allocate parameter data\n");
		goto bad;
	}
	isp->isp_osinfo.pc.ptr = malloc(xsize, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (isp->isp_osinfo.pc.ptr == NULL) {
		device_printf(dev, "cannot allocate parameter data\n");
		goto bad;
	}

	/*
	 * Now that we know who we are (roughly) get/set specific options
	 */
	for (i = 0; i < isp->isp_nchan; i++) {
		isp_get_specific_options(dev, i, isp);
	}

	isp->isp_osinfo.fw = NULL;
	if (isp->isp_osinfo.fw == NULL) {
		snprintf(fwname, sizeof (fwname), "isp_%04x", did);
		isp->isp_osinfo.fw = firmware_get(fwname);
	}
	if (isp->isp_osinfo.fw != NULL) {
		isp_prt(isp, ISP_LOGCONFIG, "loaded firmware %s", fwname);
		isp->isp_mdvec->dv_ispfw = isp->isp_osinfo.fw->data;
	}

	/*
	 * Make sure that SERR, PERR, WRITE INVALIDATE and BUSMASTER are set.
	 */
	cmd = pci_read_config(dev, PCIR_COMMAND, 2);
	cmd |= PCIM_CMD_SEREN | PCIM_CMD_PERRESPEN | PCIM_CMD_BUSMASTEREN | PCIM_CMD_INVEN;
	if (IS_2300(isp)) {	/* per QLogic errata */
		cmd &= ~PCIM_CMD_INVEN;
	}
	if (IS_2322(isp) || pci_get_devid(dev) == PCI_QLOGIC_ISP6312) {
		cmd &= ~PCIM_CMD_INTX_DISABLE;
	}
	if (IS_24XX(isp)) {
		cmd &= ~PCIM_CMD_INTX_DISABLE;
	}
	pci_write_config(dev, PCIR_COMMAND, cmd, 2);

	/*
	 * Make sure the Cache Line Size register is set sensibly.
	 */
	data = pci_read_config(dev, PCIR_CACHELNSZ, 1);
	if (data == 0 || (linesz != PCI_DFLT_LNSZ && data != linesz)) {
		isp_prt(isp, ISP_LOGDEBUG0, "set PCI line size to %d from %d", linesz, data);
		data = linesz;
		pci_write_config(dev, PCIR_CACHELNSZ, data, 1);
	}

	/*
	 * Make sure the Latency Timer is sane.
	 */
	data = pci_read_config(dev, PCIR_LATTIMER, 1);
	if (data < PCI_DFLT_LTNCY) {
		data = PCI_DFLT_LTNCY;
		isp_prt(isp, ISP_LOGDEBUG0, "set PCI latency to %d", data);
		pci_write_config(dev, PCIR_LATTIMER, data, 1);
	}

	/*
	 * Make sure we've disabled the ROM.
	 */
	data = pci_read_config(dev, PCIR_ROMADDR, 4);
	data &= ~1;
	pci_write_config(dev, PCIR_ROMADDR, data, 4);

	/*
	 * Last minute checks...
	 */
	if (IS_23XX(isp) || IS_24XX(isp)) {
		isp->isp_port = pci_get_function(dev);
	}

	/*
	 * Make sure we're in reset state.
	 */
	ISP_LOCK(isp);
	if (isp_reinit(isp, 1) != 0) {
		ISP_UNLOCK(isp);
		goto bad;
	}
	ISP_UNLOCK(isp);
	if (isp_attach(isp)) {
		ISP_LOCK(isp);
		isp_shutdown(isp);
		ISP_UNLOCK(isp);
		goto bad;
	}
	return (0);

bad:
	if (isp->isp_osinfo.fw == NULL && !IS_26XX(isp)) {
		/*
		 * Failure to attach at boot time might have been caused
		 * by a missing ispfw(4).  Except for for 16Gb adapters,
		 * there's no loadable firmware for them.
		 */
		isp_prt(isp, ISP_LOGWARN, "See the ispfw(4) man page on "
		    "how to load known good firmware at boot time");
	}
	for (i = 0; i < isp->isp_nirq; i++) {
		(void) bus_teardown_intr(dev, pcs->irq[i].irq, pcs->irq[i].ih);
		(void) bus_release_resource(dev, SYS_RES_IRQ, pcs->irq[i].iqd,
		    pcs->irq[0].irq);
	}
	if (pcs->msicount) {
		pci_release_msi(dev);
	}
	if (pcs->regs)
		(void) bus_release_resource(dev, pcs->rtp, pcs->rgd, pcs->regs);
	if (pcs->regs1)
		(void) bus_release_resource(dev, pcs->rtp1, pcs->rgd1, pcs->regs1);
	if (pcs->regs2)
		(void) bus_release_resource(dev, pcs->rtp2, pcs->rgd2, pcs->regs2);
	if (pcs->pci_isp.isp_param) {
		free(pcs->pci_isp.isp_param, M_DEVBUF);
		pcs->pci_isp.isp_param = NULL;
	}
	if (pcs->pci_isp.isp_osinfo.pc.ptr) {
		free(pcs->pci_isp.isp_osinfo.pc.ptr, M_DEVBUF);
		pcs->pci_isp.isp_osinfo.pc.ptr = NULL;
	}
	mtx_destroy(&isp->isp_lock);
	return (ENXIO);
}