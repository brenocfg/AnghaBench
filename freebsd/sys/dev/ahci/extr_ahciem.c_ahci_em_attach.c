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
struct cam_devq {int dummy; } ;
struct ahci_enclosure {int channels; int ichannels; int capsem; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * r_memc; int /*<<< orphan*/ * r_memt; int /*<<< orphan*/ * r_memr; int /*<<< orphan*/ * sim; TYPE_1__* leds; int /*<<< orphan*/  path; int /*<<< orphan*/  quirks; void* dev; } ;
struct ahci_controller {int channels; int ichannels; int /*<<< orphan*/  quirks; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int num; void* led; void* dev; } ;

/* Variables and functions */
 int AHCI_EM_ALHD ; 
 int AHCI_EM_LED ; 
 int AHCI_EM_PM ; 
 int AHCI_EM_SAFTE ; 
 int AHCI_EM_SES2 ; 
 int AHCI_EM_SGPIO ; 
 int AHCI_EM_SMB ; 
 int AHCI_EM_XMT ; 
 int AHCI_NUM_LEDS ; 
 int ATA_INL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ATA_IRQ_RID ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahci_em_led ; 
 scalar_t__ ahci_em_reset (void*) ; 
 int /*<<< orphan*/  ahciemaction ; 
 int /*<<< orphan*/  ahciempoll ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ahci_enclosure*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 char* device_get_nameunit (void*) ; 
 void* device_get_parent (void*) ; 
 void* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_get_unit (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 void* led_create (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahci_em_attach(device_t dev)
{
	device_t parent = device_get_parent(dev);
	struct ahci_controller *ctlr = device_get_softc(parent);
	struct ahci_enclosure *enc = device_get_softc(dev);
	struct cam_devq *devq;
	int i, c, rid, error;
	char buf[32];

	enc->dev = dev;
	enc->quirks = ctlr->quirks;
	enc->channels = ctlr->channels;
	enc->ichannels = ctlr->ichannels;
	mtx_init(&enc->mtx, "AHCI enclosure lock", NULL, MTX_DEF);
	rid = 0;
	if (!(enc->r_memc = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE))) {
		mtx_destroy(&enc->mtx);
		return (ENXIO);
	}
	enc->capsem = ATA_INL(enc->r_memc, 0);
	rid = 1;
	if (!(enc->r_memt = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE))) {
		error = ENXIO;
		goto err0;
	}
	if ((enc->capsem & (AHCI_EM_XMT | AHCI_EM_SMB)) == 0) {
		rid = 2;
		if (!(enc->r_memr = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		    &rid, RF_ACTIVE))) {
			error = ENXIO;
			goto err0;
		}
	} else
		enc->r_memr = NULL;
	mtx_lock(&enc->mtx);
	if (ahci_em_reset(dev) != 0) {
	    error = ENXIO;
	    goto err1;
	}
	rid = ATA_IRQ_RID;
	/* Create the device queue for our SIM. */
	devq = cam_simq_alloc(1);
	if (devq == NULL) {
		device_printf(dev, "Unable to allocate SIM queue\n");
		error = ENOMEM;
		goto err1;
	}
	/* Construct SIM entry */
	enc->sim = cam_sim_alloc(ahciemaction, ahciempoll, "ahciem", enc,
	    device_get_unit(dev), &enc->mtx,
	    1, 0, devq);
	if (enc->sim == NULL) {
		cam_simq_free(devq);
		device_printf(dev, "Unable to allocate SIM\n");
		error = ENOMEM;
		goto err1;
	}
	if (xpt_bus_register(enc->sim, dev, 0) != CAM_SUCCESS) {
		device_printf(dev, "unable to register xpt bus\n");
		error = ENXIO;
		goto err2;
	}
	if (xpt_create_path(&enc->path, /*periph*/NULL, cam_sim_path(enc->sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		device_printf(dev, "Unable to create path\n");
		error = ENXIO;
		goto err3;
	}
	mtx_unlock(&enc->mtx);
	if (bootverbose) {
		device_printf(dev, "Caps:%s%s%s%s%s%s%s%s\n",
		    (enc->capsem & AHCI_EM_PM) ? " PM":"",
		    (enc->capsem & AHCI_EM_ALHD) ? " ALHD":"",
		    (enc->capsem & AHCI_EM_XMT) ? " XMT":"",
		    (enc->capsem & AHCI_EM_SMB) ? " SMB":"",
		    (enc->capsem & AHCI_EM_SGPIO) ? " SGPIO":"",
		    (enc->capsem & AHCI_EM_SES2) ? " SES-2":"",
		    (enc->capsem & AHCI_EM_SAFTE) ? " SAF-TE":"",
		    (enc->capsem & AHCI_EM_LED) ? " LED":"");
	}
	if ((enc->capsem & AHCI_EM_LED)) {
		for (c = 0; c < enc->channels; c++) {
			if ((enc->ichannels & (1 << c)) == 0)
				continue;
			for (i = 0; i < AHCI_NUM_LEDS; i++) {
				enc->leds[c * AHCI_NUM_LEDS + i].dev = dev;
				enc->leds[c * AHCI_NUM_LEDS + i].num =
				    c * AHCI_NUM_LEDS + i;
			}
			if ((enc->capsem & AHCI_EM_ALHD) == 0) {
				snprintf(buf, sizeof(buf), "%s.%d.act",
				    device_get_nameunit(parent), c);
				enc->leds[c * AHCI_NUM_LEDS + 0].led =
				    led_create(ahci_em_led,
				    &enc->leds[c * AHCI_NUM_LEDS + 0], buf);
			}
			snprintf(buf, sizeof(buf), "%s.%d.locate",
			    device_get_nameunit(parent), c);
			enc->leds[c * AHCI_NUM_LEDS + 1].led =
			    led_create(ahci_em_led,
			    &enc->leds[c * AHCI_NUM_LEDS + 1], buf);
			snprintf(buf, sizeof(buf), "%s.%d.fault",
			    device_get_nameunit(parent), c);
			enc->leds[c * AHCI_NUM_LEDS + 2].led =
			    led_create(ahci_em_led,
			    &enc->leds[c * AHCI_NUM_LEDS + 2], buf);
		}
	}
	return (0);

err3:
	xpt_bus_deregister(cam_sim_path(enc->sim));
err2:
	cam_sim_free(enc->sim, /*free_devq*/TRUE);
err1:
	mtx_unlock(&enc->mtx);
	if (enc->r_memr)
		bus_release_resource(dev, SYS_RES_MEMORY, 2, enc->r_memr);
err0:
	if (enc->r_memt)
		bus_release_resource(dev, SYS_RES_MEMORY, 1, enc->r_memt);
	bus_release_resource(dev, SYS_RES_MEMORY, 0, enc->r_memc);
	mtx_destroy(&enc->mtx);
	return (error);
}