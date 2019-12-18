#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {char* rm_descr; int /*<<< orphan*/  rm_type; int /*<<< orphan*/  rm_end; int /*<<< orphan*/  rm_start; } ;
struct mvs_controller {int channels; int quirks; int ccc; int cccc; TYPE_1__ sc_iomem; int /*<<< orphan*/  r_mem; scalar_t__ r_rid; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_6__ {scalar_t__ id; scalar_t__ rev; int ports; int quirks; } ;

/* Variables and functions */
 scalar_t__ ATA_INL (int /*<<< orphan*/ ,scalar_t__) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int MVS_Q_GENI ; 
 int MVS_Q_GENII ; 
 int MVS_Q_GENIIE ; 
 int MVS_Q_SOC65 ; 
 scalar_t__ PORT_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 scalar_t__ SATA_PHYCFG_OFS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_ctlr_setup (int /*<<< orphan*/ *) ; 
 TYPE_4__* mvs_ids ; 
 scalar_t__ mvs_setup_interrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  rman_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  rman_get_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_id (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
mvs_attach(device_t dev)
{
	struct mvs_controller *ctlr = device_get_softc(dev);
	device_t child;
	int	error, unit, i;
	uint32_t devid, revid;

	soc_id(&devid, &revid);
	ctlr->dev = dev;
	i = 0;
	while (mvs_ids[i].id != 0 &&
	    (mvs_ids[i].id != devid ||
	     mvs_ids[i].rev > revid))
		i++;
	ctlr->channels = mvs_ids[i].ports;
	ctlr->quirks = mvs_ids[i].quirks;
	ctlr->ccc = 0;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "ccc", &ctlr->ccc);
	ctlr->cccc = 8;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "cccc", &ctlr->cccc);
	if (ctlr->ccc == 0 || ctlr->cccc == 0) {
		ctlr->ccc = 0;
		ctlr->cccc = 0;
	}
	if (ctlr->ccc > 100000)
		ctlr->ccc = 100000;
	device_printf(dev,
	    "Gen-%s, %d %sGbps ports, Port Multiplier %s%s\n",
	    ((ctlr->quirks & MVS_Q_GENI) ? "I" :
	     ((ctlr->quirks & MVS_Q_GENII) ? "II" : "IIe")),
	    ctlr->channels,
	    ((ctlr->quirks & MVS_Q_GENI) ? "1.5" : "3"),
	    ((ctlr->quirks & MVS_Q_GENI) ?
	    "not supported" : "supported"),
	    ((ctlr->quirks & MVS_Q_GENIIE) ?
	    " with FBS" : ""));
	mtx_init(&ctlr->mtx, "MVS controller lock", NULL, MTX_DEF);
	/* We should have a memory BAR(0). */
	ctlr->r_rid = 0;
	if (!(ctlr->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &ctlr->r_rid, RF_ACTIVE)))
		return ENXIO;
	if (ATA_INL(ctlr->r_mem, PORT_BASE(0) + SATA_PHYCFG_OFS) != 0)
		ctlr->quirks |= MVS_Q_SOC65;
	/* Setup our own memory management for channels. */
	ctlr->sc_iomem.rm_start = rman_get_start(ctlr->r_mem);
	ctlr->sc_iomem.rm_end = rman_get_end(ctlr->r_mem);
	ctlr->sc_iomem.rm_type = RMAN_ARRAY;
	ctlr->sc_iomem.rm_descr = "I/O memory addresses";
	if ((error = rman_init(&ctlr->sc_iomem)) != 0) {
		bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid, ctlr->r_mem);
		return (error);
	}
	if ((error = rman_manage_region(&ctlr->sc_iomem,
	    rman_get_start(ctlr->r_mem), rman_get_end(ctlr->r_mem))) != 0) {
		bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid, ctlr->r_mem);
		rman_fini(&ctlr->sc_iomem);
		return (error);
	}
	mvs_ctlr_setup(dev);
	/* Setup interrupts. */
	if (mvs_setup_interrupt(dev)) {
		bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid, ctlr->r_mem);
		rman_fini(&ctlr->sc_iomem);
		return ENXIO;
	}
	/* Attach all channels on this controller */
	for (unit = 0; unit < ctlr->channels; unit++) {
		child = device_add_child(dev, "mvsch", -1);
		if (child == NULL)
			device_printf(dev, "failed to add channel device\n");
		else
			device_set_ivars(child, (void *)(intptr_t)unit);
	}
	bus_generic_attach(dev);
	return 0;
}