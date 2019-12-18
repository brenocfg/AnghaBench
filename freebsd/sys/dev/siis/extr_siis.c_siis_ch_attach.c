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
struct siis_controller {int /*<<< orphan*/  quirks; } ;
struct siis_channel {intptr_t unit; int pm_level; int /*<<< orphan*/  mtx; void* r_mem; void* r_irq; int /*<<< orphan*/ * sim; int /*<<< orphan*/  led; int /*<<< orphan*/  path; int /*<<< orphan*/  ih; TYPE_1__* user; TYPE_1__* curr; int /*<<< orphan*/  quirks; int /*<<< orphan*/  dev; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int revision; int bytecount; int /*<<< orphan*/  caps; int /*<<< orphan*/  tags; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 int ATA_IRQ_RID ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CTS_SATA_CAPS_H_AN ; 
 int /*<<< orphan*/  CTS_SATA_CAPS_H_PMREQ ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SIIS_MAX_SLOTS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct siis_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  led_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  siis_ch_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_ch_intr_locked ; 
 int /*<<< orphan*/  siis_ch_led ; 
 int /*<<< orphan*/  siis_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_slotsalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siisaction ; 
 int /*<<< orphan*/  siispoll ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siis_ch_attach(device_t dev)
{
	struct siis_controller *ctlr = device_get_softc(device_get_parent(dev));
	struct siis_channel *ch = device_get_softc(dev);
	struct cam_devq *devq;
	int rid, error, i, sata_rev = 0;

	ch->dev = dev;
	ch->unit = (intptr_t)device_get_ivars(dev);
	ch->quirks = ctlr->quirks;
	ch->pm_level = 0;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "pm_level", &ch->pm_level);
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "sata_rev", &sata_rev);
	for (i = 0; i < 16; i++) {
		ch->user[i].revision = sata_rev;
		ch->user[i].mode = 0;
		ch->user[i].bytecount = 8192;
		ch->user[i].tags = SIIS_MAX_SLOTS;
		ch->curr[i] = ch->user[i];
		if (ch->pm_level)
			ch->user[i].caps = CTS_SATA_CAPS_H_PMREQ;
		ch->user[i].caps |= CTS_SATA_CAPS_H_AN;
	}
	mtx_init(&ch->mtx, "SIIS channel lock", NULL, MTX_DEF);
	rid = ch->unit;
	if (!(ch->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE)))
		return (ENXIO);
	siis_dmainit(dev);
	siis_slotsalloc(dev);
	siis_ch_init(dev);
	mtx_lock(&ch->mtx);
	rid = ATA_IRQ_RID;
	if (!(ch->r_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &rid, RF_SHAREABLE | RF_ACTIVE))) {
		device_printf(dev, "Unable to map interrupt\n");
		error = ENXIO;
		goto err0;
	}
	if ((bus_setup_intr(dev, ch->r_irq, ATA_INTR_FLAGS, NULL,
	    siis_ch_intr_locked, dev, &ch->ih))) {
		device_printf(dev, "Unable to setup interrupt\n");
		error = ENXIO;
		goto err1;
	}
	/* Create the device queue for our SIM. */
	devq = cam_simq_alloc(SIIS_MAX_SLOTS);
	if (devq == NULL) {
		device_printf(dev, "Unable to allocate simq\n");
		error = ENOMEM;
		goto err1;
	}
	/* Construct SIM entry */
	ch->sim = cam_sim_alloc(siisaction, siispoll, "siisch", ch,
	    device_get_unit(dev), &ch->mtx, 2, SIIS_MAX_SLOTS, devq);
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
	mtx_unlock(&ch->mtx);
	ch->led = led_create(siis_ch_led, dev, device_get_nameunit(dev));
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