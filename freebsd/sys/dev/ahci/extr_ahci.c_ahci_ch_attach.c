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
typedef  int u_int32_t ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct mtx {int dummy; } ;
struct cam_devq {int dummy; } ;
struct ahci_controller {int caps; int caps2; int quirks; scalar_t__ direct; void* r_mem; int /*<<< orphan*/  subdeviceid; int /*<<< orphan*/  subvendorid; int /*<<< orphan*/  deviceid; int /*<<< orphan*/  vendorid; int /*<<< orphan*/  ch_start; } ;
struct ahci_channel {intptr_t unit; int caps; int caps2; int quirks; int numslots; int pm_level; int chcaps; int chscaps; int /*<<< orphan*/  mtx; void* r_mem; void* r_irq; int /*<<< orphan*/ * sim; int /*<<< orphan*/  pm_timer; int /*<<< orphan*/  path; int /*<<< orphan*/  ih; TYPE_1__* user; TYPE_1__* curr; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  doneq; int /*<<< orphan*/  subdeviceid; int /*<<< orphan*/  subvendorid; int /*<<< orphan*/  deviceid; int /*<<< orphan*/  vendorid; int /*<<< orphan*/  start; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int revision; int bytecount; int tags; int caps; scalar_t__ mode; } ;

/* Variables and functions */
 int AHCI_CAP2_SDS ; 
 int AHCI_CAP_FBSS ; 
 int AHCI_CAP_NCS ; 
 int AHCI_CAP_NCS_SHIFT ; 
 int AHCI_CAP_SNCQ ; 
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int AHCI_P_CMD_CPD ; 
 int AHCI_P_CMD_ESP ; 
 int AHCI_P_CMD_FBSCP ; 
 int AHCI_P_CMD_HPCP ; 
 int AHCI_P_CMD_MPSP ; 
 int /*<<< orphan*/  AHCI_P_DEVSLP ; 
 int AHCI_P_DEVSLP_DSP ; 
 int AHCI_Q_NOCCS ; 
 int AHCI_Q_SATA1_UNIT0 ; 
 int AHCI_Q_SATA2 ; 
 int /*<<< orphan*/  AHCI_VS ; 
 void* ATA_INL (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 int ATA_IRQ_RID ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int CTS_SATA_CAPS_D_APST ; 
 int CTS_SATA_CAPS_D_PMREQ ; 
 int CTS_SATA_CAPS_H_AN ; 
 int CTS_SATA_CAPS_H_APST ; 
 int CTS_SATA_CAPS_H_DMAAA ; 
 int CTS_SATA_CAPS_H_PMREQ ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ahci_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahci_attached (int /*<<< orphan*/ ,struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_ch_disablephy_proc ; 
 int /*<<< orphan*/  ahci_ch_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_ch_intr ; 
 int /*<<< orphan*/  ahci_ch_intr_direct ; 
 int /*<<< orphan*/  ahci_ch_pm ; 
 int /*<<< orphan*/  ahci_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_slotsalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahciaction ; 
 int /*<<< orphan*/  ahcipoll ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahci_channel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ahci_channel*) ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ahci_channel*,int /*<<< orphan*/ ,struct mtx*,int,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hz ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahci_ch_attach(device_t dev)
{
	struct ahci_controller *ctlr = device_get_softc(device_get_parent(dev));
	struct ahci_channel *ch = device_get_softc(dev);
	struct cam_devq *devq;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	int rid, error, i, sata_rev = 0;
	u_int32_t version;

	ch->dev = dev;
	ch->unit = (intptr_t)device_get_ivars(dev);
	ch->caps = ctlr->caps;
	ch->caps2 = ctlr->caps2;
	ch->start = ctlr->ch_start;
	ch->quirks = ctlr->quirks;
	ch->vendorid = ctlr->vendorid;
	ch->deviceid = ctlr->deviceid;
	ch->subvendorid = ctlr->subvendorid;
	ch->subdeviceid = ctlr->subdeviceid;
	ch->numslots = ((ch->caps & AHCI_CAP_NCS) >> AHCI_CAP_NCS_SHIFT) + 1;
	mtx_init(&ch->mtx, "AHCI channel lock", NULL, MTX_DEF);
	ch->pm_level = 0;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "pm_level", &ch->pm_level);
	STAILQ_INIT(&ch->doneq);
	if (ch->pm_level > 3)
		callout_init_mtx(&ch->pm_timer, &ch->mtx, 0);
	callout_init_mtx(&ch->reset_timer, &ch->mtx, 0);
	/* JMicron external ports (0) sometimes limited */
	if ((ctlr->quirks & AHCI_Q_SATA1_UNIT0) && ch->unit == 0)
		sata_rev = 1;
	if (ch->quirks & AHCI_Q_SATA2)
		sata_rev = 2;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "sata_rev", &sata_rev);
	for (i = 0; i < 16; i++) {
		ch->user[i].revision = sata_rev;
		ch->user[i].mode = 0;
		ch->user[i].bytecount = 8192;
		ch->user[i].tags = ch->numslots;
		ch->user[i].caps = 0;
		ch->curr[i] = ch->user[i];
		if (ch->pm_level) {
			ch->user[i].caps = CTS_SATA_CAPS_H_PMREQ |
			    CTS_SATA_CAPS_H_APST |
			    CTS_SATA_CAPS_D_PMREQ | CTS_SATA_CAPS_D_APST;
		}
		ch->user[i].caps |= CTS_SATA_CAPS_H_DMAAA |
		    CTS_SATA_CAPS_H_AN;
	}
	rid = 0;
	if (!(ch->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE)))
		return (ENXIO);
	ch->chcaps = ATA_INL(ch->r_mem, AHCI_P_CMD);
	version = ATA_INL(ctlr->r_mem, AHCI_VS);
	if (version < 0x00010200 && (ctlr->caps & AHCI_CAP_FBSS))
		ch->chcaps |= AHCI_P_CMD_FBSCP;
	if (ch->caps2 & AHCI_CAP2_SDS)
		ch->chscaps = ATA_INL(ch->r_mem, AHCI_P_DEVSLP);
	if (bootverbose) {
		device_printf(dev, "Caps:%s%s%s%s%s%s\n",
		    (ch->chcaps & AHCI_P_CMD_HPCP) ? " HPCP":"",
		    (ch->chcaps & AHCI_P_CMD_MPSP) ? " MPSP":"",
		    (ch->chcaps & AHCI_P_CMD_CPD) ? " CPD":"",
		    (ch->chcaps & AHCI_P_CMD_ESP) ? " ESP":"",
		    (ch->chcaps & AHCI_P_CMD_FBSCP) ? " FBSCP":"",
		    (ch->chscaps & AHCI_P_DEVSLP_DSP) ? " DSP":"");
	}
	ahci_dmainit(dev);
	ahci_slotsalloc(dev);
	mtx_lock(&ch->mtx);
	ahci_ch_init(dev);
	rid = ATA_IRQ_RID;
	if (!(ch->r_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &rid, RF_SHAREABLE | RF_ACTIVE))) {
		device_printf(dev, "Unable to map interrupt\n");
		error = ENXIO;
		goto err0;
	}
	if ((bus_setup_intr(dev, ch->r_irq, ATA_INTR_FLAGS, NULL,
	    ctlr->direct ? ahci_ch_intr_direct : ahci_ch_intr,
	    ch, &ch->ih))) {
		device_printf(dev, "Unable to setup interrupt\n");
		error = ENXIO;
		goto err1;
	}
	/* Create the device queue for our SIM. */
	devq = cam_simq_alloc(ch->numslots);
	if (devq == NULL) {
		device_printf(dev, "Unable to allocate simq\n");
		error = ENOMEM;
		goto err1;
	}
	/* Construct SIM entry */
	ch->sim = cam_sim_alloc(ahciaction, ahcipoll, "ahcich", ch,
	    device_get_unit(dev), (struct mtx *)&ch->mtx,
	    (ch->quirks & AHCI_Q_NOCCS) ? 1 : min(2, ch->numslots),
	    (ch->caps & AHCI_CAP_SNCQ) ? ch->numslots : 0,
	    devq);
	if (ch->sim == NULL) {
		cam_simq_free(devq);
		device_printf(dev, "unable to allocate sim\n");
		error = ENOMEM;
		goto err1;
	}
	if (xpt_bus_register(ch->sim, dev, 0) != CAM_SUCCESS) {
		device_printf(dev, "unable to register xpt bus\n");
		error = ENXIO;
		goto err2;
	}
	if (xpt_create_path(&ch->path, /*periph*/NULL, cam_sim_path(ch->sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		device_printf(dev, "unable to create path\n");
		error = ENXIO;
		goto err3;
	}
	if (ch->pm_level > 3) {
		callout_reset(&ch->pm_timer,
		    (ch->pm_level == 4) ? hz / 1000 : hz / 8,
		    ahci_ch_pm, ch);
	}
	mtx_unlock(&ch->mtx);
	ahci_attached(device_get_parent(dev), ch);
	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO, "disable_phy",
	    CTLFLAG_RW | CTLTYPE_UINT, ch, 0, ahci_ch_disablephy_proc, "IU",
	    "Disable PHY");
	return (0);

err3:
	xpt_bus_deregister(cam_sim_path(ch->sim));
err2:
	cam_sim_free(ch->sim, /*free_devq*/TRUE);
err1:
	bus_release_resource(dev, SYS_RES_IRQ, ATA_IRQ_RID, ch->r_irq);
err0:
	bus_release_resource(dev, SYS_RES_MEMORY, ch->unit, ch->r_mem);
	mtx_unlock(&ch->mtx);
	mtx_destroy(&ch->mtx);
	return (error);
}