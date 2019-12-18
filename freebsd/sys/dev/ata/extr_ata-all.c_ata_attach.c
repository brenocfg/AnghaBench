#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtx {int dummy; } ;
struct cam_devq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* alloc ) (int /*<<< orphan*/ ) ;} ;
struct ata_channel {int flags; int pm_level; int /*<<< orphan*/  poll_callout; int /*<<< orphan*/  state_mtx; scalar_t__ r_irq; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/  ih; TYPE_2__ dma; TYPE_1__* user; TYPE_1__* curr; int /*<<< orphan*/  conntask; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int revision; int mode; int bytecount; int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_IDLE ; 
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 int ATA_IRQ_RID ; 
 int ATA_NO_48BIT_DMA ; 
 int ATA_PERIODIC_POLL ; 
 int ATA_SATA ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CTS_ATA_CAPS_H_DMA48 ; 
 int /*<<< orphan*/  CTS_SATA_CAPS_D_PMREQ ; 
 int /*<<< orphan*/  CTS_SATA_CAPS_H_PMREQ ; 
 int EEXIST ; 
 int ENOMEM ; 
 int ENXIO ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ata_conn_event ; 
 int /*<<< orphan*/  ata_interrupt ; 
 int /*<<< orphan*/  ata_periodic_poll ; 
 int ata_str2mode (char const*) ; 
 int /*<<< orphan*/  ataaction ; 
 int /*<<< orphan*/  atapoll ; 
 scalar_t__ bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ata_channel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ata_channel*) ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ata_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ata_attach(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    int error, rid;
    struct cam_devq *devq;
    const char *res;
    char buf[64];
    int i, mode;

    /* check that we have a virgin channel to attach */
    if (ch->r_irq)
	return EEXIST;

    /* initialize the softc basics */
    ch->dev = dev;
    ch->state = ATA_IDLE;
    bzero(&ch->state_mtx, sizeof(struct mtx));
    mtx_init(&ch->state_mtx, "ATA state lock", NULL, MTX_DEF);
    TASK_INIT(&ch->conntask, 0, ata_conn_event, dev);
	for (i = 0; i < 16; i++) {
		ch->user[i].revision = 0;
		snprintf(buf, sizeof(buf), "dev%d.sata_rev", i);
		if (resource_int_value(device_get_name(dev),
		    device_get_unit(dev), buf, &mode) != 0 &&
		    resource_int_value(device_get_name(dev),
		    device_get_unit(dev), "sata_rev", &mode) != 0)
			mode = -1;
		if (mode >= 0)
			ch->user[i].revision = mode;
		ch->user[i].mode = 0;
		snprintf(buf, sizeof(buf), "dev%d.mode", i);
		if (resource_string_value(device_get_name(dev),
		    device_get_unit(dev), buf, &res) == 0)
			mode = ata_str2mode(res);
		else if (resource_string_value(device_get_name(dev),
		    device_get_unit(dev), "mode", &res) == 0)
			mode = ata_str2mode(res);
		else
			mode = -1;
		if (mode >= 0)
			ch->user[i].mode = mode;
		if (ch->flags & ATA_SATA)
			ch->user[i].bytecount = 8192;
		else
			ch->user[i].bytecount = MAXPHYS;
		ch->user[i].caps = 0;
		ch->curr[i] = ch->user[i];
		if (ch->flags & ATA_SATA) {
			if (ch->pm_level > 0)
				ch->user[i].caps |= CTS_SATA_CAPS_H_PMREQ;
			if (ch->pm_level > 1)
				ch->user[i].caps |= CTS_SATA_CAPS_D_PMREQ;
		} else {
			if (!(ch->flags & ATA_NO_48BIT_DMA))
				ch->user[i].caps |= CTS_ATA_CAPS_H_DMA48;
		}
	}
	callout_init(&ch->poll_callout, 1);

    /* allocate DMA resources if DMA HW present*/
    if (ch->dma.alloc)
	ch->dma.alloc(dev);

    /* setup interrupt delivery */
    rid = ATA_IRQ_RID;
    ch->r_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
				       RF_SHAREABLE | RF_ACTIVE);
    if (!ch->r_irq) {
	device_printf(dev, "unable to allocate interrupt\n");
	return ENXIO;
    }
    if ((error = bus_setup_intr(dev, ch->r_irq, ATA_INTR_FLAGS, NULL,
				ata_interrupt, ch, &ch->ih))) {
	bus_release_resource(dev, SYS_RES_IRQ, rid, ch->r_irq);
	device_printf(dev, "unable to setup interrupt\n");
	return error;
    }

	if (ch->flags & ATA_PERIODIC_POLL)
		callout_reset(&ch->poll_callout, hz, ata_periodic_poll, ch);
	mtx_lock(&ch->state_mtx);
	/* Create the device queue for our SIM. */
	devq = cam_simq_alloc(1);
	if (devq == NULL) {
		device_printf(dev, "Unable to allocate simq\n");
		error = ENOMEM;
		goto err1;
	}
	/* Construct SIM entry */
	ch->sim = cam_sim_alloc(ataaction, atapoll, "ata", ch,
	    device_get_unit(dev), &ch->state_mtx, 1, 0, devq);
	if (ch->sim == NULL) {
		device_printf(dev, "unable to allocate sim\n");
		cam_simq_free(devq);
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
	mtx_unlock(&ch->state_mtx);
	return (0);

err3:
	xpt_bus_deregister(cam_sim_path(ch->sim));
err2:
	cam_sim_free(ch->sim, /*free_devq*/TRUE);
	ch->sim = NULL;
err1:
	bus_release_resource(dev, SYS_RES_IRQ, rid, ch->r_irq);
	mtx_unlock(&ch->state_mtx);
	if (ch->flags & ATA_PERIODIC_POLL)
		callout_drain(&ch->poll_callout);
	return (error);
}