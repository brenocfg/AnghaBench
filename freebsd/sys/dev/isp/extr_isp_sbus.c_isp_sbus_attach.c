#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_25__ {int dv_clock; int dv_conf1; int /*<<< orphan*/ * dv_ispfw; } ;
struct TYPE_22__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_23__ {TYPE_8__* fw; TYPE_1__ pc; } ;
struct TYPE_24__ {int isp_nchan; int isp_nirq; int isp_dblev; int /*<<< orphan*/  isp_lock; int /*<<< orphan*/  isp_confopts; TYPE_4__* isp_mdvec; TYPE_2__ isp_osinfo; scalar_t__ isp_revision; int /*<<< orphan*/ * isp_param; int /*<<< orphan*/  isp_type; int /*<<< orphan*/  isp_bustype; int /*<<< orphan*/ * isp_regs; void* isp_dev; } ;
struct isp_sbussoftc {int /*<<< orphan*/ * regs; scalar_t__ rgd; int /*<<< orphan*/ * irq; scalar_t__ iqd; int /*<<< orphan*/  ih; TYPE_4__ sbus_mdvec; int /*<<< orphan*/  sbus_spi; int /*<<< orphan*/  sbus_param; int /*<<< orphan*/ * sbus_poff; void* sbus_dev; TYPE_3__ sbus_isp; } ;
typedef  TYPE_3__ ispsoftc_t ;
typedef  void* device_t ;
struct TYPE_26__ {void const* data; } ;
struct TYPE_21__ {int def_role; } ;
struct TYPE_20__ {int iid; } ;
struct TYPE_19__ {int isp_ptisp; } ;

/* Variables and functions */
 size_t BIU_BLOCK ; 
 int BIU_BURST_ENABLE ; 
 int /*<<< orphan*/  BIU_REGS_OFF ; 
 int BIU_SBUS_CONF1_BURST8 ; 
 int BIU_SBUS_CONF1_FIFO_16 ; 
 int BIU_SBUS_CONF1_FIFO_32 ; 
 int BIU_SBUS_CONF1_FIFO_8 ; 
 size_t DMA_BLOCK ; 
 int /*<<< orphan*/  DMA_REGS_OFF ; 
 int ENXIO ; 
 int /*<<< orphan*/  ISP_BT_SBUS ; 
 int /*<<< orphan*/  ISP_CFG_NONVRAM ; 
 int /*<<< orphan*/  ISP_CFG_NORELOAD ; 
 int /*<<< orphan*/  ISP_CFG_OWNLOOPID ; 
 int ISP_DEFAULT_ROLES ; 
 TYPE_17__* ISP_FC_PC (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_HA_SCSI_UNKNOWN ; 
 int /*<<< orphan*/  ISP_IFLAGS ; 
 int /*<<< orphan*/  ISP_LOCK (TYPE_3__*) ; 
 int ISP_LOGCONFIG ; 
 int ISP_LOGERR ; 
 int ISP_LOGINFO ; 
 int ISP_LOGWARN ; 
 int ISP_ROLE_INITIATOR ; 
 int ISP_ROLE_TARGET ; 
 TYPE_14__* ISP_SPI_PC (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_3__*) ; 
 scalar_t__ IS_FC (TYPE_3__*) ; 
 size_t MBOX_BLOCK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int OF_getscsinitid (void*) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 size_t RISC_BLOCK ; 
 int SBUS_BURST_32 ; 
 int /*<<< orphan*/  SBUS_MBOX_REGS_OFF ; 
 int /*<<< orphan*/  SBUS_RISC_REGS_OFF ; 
 int /*<<< orphan*/  SBUS_SXP_REGS_OFF ; 
 TYPE_10__* SDPARAM (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t SXP_BLOCK ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 size_t _BLK_REG_SHFT ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (void*) ; 
 struct isp_sbussoftc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_get_unit (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 TYPE_8__* firmware_get (char*) ; 
 scalar_t__ isp_attach (TYPE_3__*) ; 
 int /*<<< orphan*/  isp_platform_intr ; 
 scalar_t__ isp_reinit (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isp_shutdown (TYPE_3__*) ; 
 TYPE_4__ mdvec ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_name (void*) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int sbus_get_burstsz (void*) ; 
 int sbus_get_clockfreq (void*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isp_sbus_attach(device_t dev)
{
	struct isp_sbussoftc *sbs = device_get_softc(dev);
	ispsoftc_t *isp = &sbs->sbus_isp;
	int tval, isp_debug, role, ispburst, default_id;

	sbs->sbus_dev = dev;
	sbs->sbus_mdvec = mdvec;
	isp->isp_dev = dev;
	mtx_init(&isp->isp_lock, "isp", NULL, MTX_DEF);

	role = 0;
	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "role", &role) == 0 &&
	    ((role & ~(ISP_ROLE_INITIATOR|ISP_ROLE_TARGET)) == 0)) {
		device_printf(dev, "setting role to 0x%x\n", role);
	} else {
		role = ISP_DEFAULT_ROLES;
	}

	sbs->irq = sbs->regs = NULL;
	sbs->rgd = sbs->iqd = 0;

	sbs->regs = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sbs->rgd,
	    RF_ACTIVE);
	if (sbs->regs == NULL) {
		device_printf(dev, "unable to map registers\n");
		goto bad;
	}

	sbs->sbus_poff[BIU_BLOCK >> _BLK_REG_SHFT] = BIU_REGS_OFF;
	sbs->sbus_poff[MBOX_BLOCK >> _BLK_REG_SHFT] = SBUS_MBOX_REGS_OFF;
	sbs->sbus_poff[SXP_BLOCK >> _BLK_REG_SHFT] = SBUS_SXP_REGS_OFF;
	sbs->sbus_poff[RISC_BLOCK >> _BLK_REG_SHFT] = SBUS_RISC_REGS_OFF;
	sbs->sbus_poff[DMA_BLOCK >> _BLK_REG_SHFT] = DMA_REGS_OFF;
	isp->isp_regs = sbs->regs;
	isp->isp_mdvec = &sbs->sbus_mdvec;
	isp->isp_bustype = ISP_BT_SBUS;
	isp->isp_type = ISP_HA_SCSI_UNKNOWN;
	isp->isp_param = &sbs->sbus_param;
	isp->isp_osinfo.pc.ptr = &sbs->sbus_spi;
	isp->isp_revision = 0;	/* XXX */
	isp->isp_nchan = 1;
	if (IS_FC(isp))
		ISP_FC_PC(isp, 0)->def_role = role;

	/*
	 * Get the clock frequency and convert it from HZ to MHz,
	 * rounding up. This defaults to 25MHz if there isn't a
	 * device specific one in the OFW device tree.
	 */
	sbs->sbus_mdvec.dv_clock = (sbus_get_clockfreq(dev) + 500000)/1000000;

	/*
	 * Now figure out what the proper burst sizes, etc., to use.
	 * Unfortunately, there is no ddi_dma_burstsizes here which
	 * walks up the tree finding the limiting burst size node (if
	 * any). We just use what's here for isp.
	 */
	ispburst = sbus_get_burstsz(dev);
	if (ispburst == 0) {
		ispburst = SBUS_BURST_32 - 1;
	}
	sbs->sbus_mdvec.dv_conf1 =  0;
	if (ispburst & (1 << 5)) {
		sbs->sbus_mdvec.dv_conf1 = BIU_SBUS_CONF1_FIFO_32;
	} else if (ispburst & (1 << 4)) {
		sbs->sbus_mdvec.dv_conf1 = BIU_SBUS_CONF1_FIFO_16;
	} else if (ispburst & (1 << 3)) {
		sbs->sbus_mdvec.dv_conf1 =
		    BIU_SBUS_CONF1_BURST8 | BIU_SBUS_CONF1_FIFO_8;
	}
	if (sbs->sbus_mdvec.dv_conf1) {
		sbs->sbus_mdvec.dv_conf1 |= BIU_BURST_ENABLE;
	}

	/*
	 * We don't trust NVRAM on SBus cards
	 */
	isp->isp_confopts |= ISP_CFG_NONVRAM;

	/*
	 * Mark things if we're a PTI SBus adapter.
	 */
	if (strcmp("PTI,ptisp", ofw_bus_get_name(dev)) == 0 ||
	    strcmp("ptisp", ofw_bus_get_name(dev)) == 0) {
		SDPARAM(isp, 0)->isp_ptisp = 1;
	}

	isp->isp_osinfo.fw = firmware_get("isp_1000");
	if (isp->isp_osinfo.fw) {
		union {
			const void *cp;
			uint16_t *sp;
		} stupid;
		stupid.cp = isp->isp_osinfo.fw->data;
		isp->isp_mdvec->dv_ispfw = stupid.sp;
	}

	tval = 0;
        if (resource_int_value(device_get_name(dev), device_get_unit(dev),
            "fwload_disable", &tval) == 0 && tval != 0) {
		isp->isp_confopts |= ISP_CFG_NORELOAD;
	}

	default_id = -1;
	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
            "iid", &tval) == 0) {
		default_id = tval;
		isp->isp_confopts |= ISP_CFG_OWNLOOPID;
	}
	if (default_id == -1) {
		default_id = OF_getscsinitid(dev);
	}
	ISP_SPI_PC(isp, 0)->iid = default_id;

	isp_debug = 0;
        (void) resource_int_value(device_get_name(dev), device_get_unit(dev),
            "debug", &isp_debug);

	sbs->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sbs->iqd,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sbs->irq == NULL) {
		device_printf(dev, "could not allocate interrupt\n");
		goto bad;
	}

	if (bus_setup_intr(dev, sbs->irq, ISP_IFLAGS, NULL, isp_platform_intr,
	    isp, &sbs->ih)) {
		device_printf(dev, "could not setup interrupt\n");
		(void) bus_release_resource(dev, SYS_RES_IRQ,
		    sbs->iqd, sbs->irq);
		goto bad;
	}
	isp->isp_nirq = 1;

	/*
	 * Set up logging levels.
	 */
	if (isp_debug) {
		isp->isp_dblev = isp_debug;
	} else {
		isp->isp_dblev = ISP_LOGWARN|ISP_LOGERR;
	}
	if (bootverbose) {
		isp->isp_dblev |= ISP_LOGCONFIG|ISP_LOGINFO;
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
	if (isp->isp_nirq > 0) {
		(void) bus_teardown_intr(dev, sbs->irq, sbs->ih);
		(void) bus_release_resource(dev, SYS_RES_IRQ, sbs->iqd,
		    sbs->irq);
	}

	if (sbs->regs) {
		(void) bus_release_resource(dev, SYS_RES_MEMORY, sbs->rgd,
		    sbs->regs);
	}
	mtx_destroy(&isp->isp_lock);
	return (ENXIO);
}