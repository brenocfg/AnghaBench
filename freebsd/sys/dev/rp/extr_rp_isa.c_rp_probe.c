#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int io_num; int /*<<< orphan*/ ** io; scalar_t__* io_rid; int /*<<< orphan*/ * bus_ctlp; int /*<<< orphan*/  ctlmask; int /*<<< orphan*/  aiop2off; int /*<<< orphan*/  aiop2rid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ISACONTROLLER_t ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FREQ_DIS ; 
 int MAX_AIOPS_PER_BOARD ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 void* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_resource_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* rp_controller ; 
 int /*<<< orphan*/  rp_isa_aiop2off ; 
 int /*<<< orphan*/  rp_isa_aiop2rid ; 
 int /*<<< orphan*/  rp_isa_ctlmask ; 
 int /*<<< orphan*/  rp_isareleaseresource (TYPE_1__*) ; 
 int /*<<< orphan*/  rp_nisadevs ; 
 int sInitController (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rp_probe(device_t dev)
{
	int unit;
	CONTROLLER_t *controller;
	int num_aiops;
	CONTROLLER_t *ctlp;
	int retval;

	/*
	 * We have no PnP RocketPort cards.
	 * (At least according to LINT)
	 */
	if (isa_get_logicalid(dev) != 0)
		return (ENXIO);

	/* We need IO port resource to configure an ISA device. */
	if (bus_get_resource_count(dev, SYS_RES_IOPORT, 0) == 0)
		return (ENXIO);

	unit = device_get_unit(dev);
	if (unit >= 4) {
		device_printf(dev, "rpprobe: unit number %d invalid.\n", unit);
		return (ENXIO);
	}
	device_printf(dev, "probing for RocketPort(ISA) unit %d.\n", unit);

	ctlp = device_get_softc(dev);
	bzero(ctlp, sizeof(*ctlp));
	ctlp->dev = dev;
	ctlp->aiop2rid = rp_isa_aiop2rid;
	ctlp->aiop2off = rp_isa_aiop2off;
	ctlp->ctlmask = rp_isa_ctlmask;

	/* The IO ports of AIOPs for an ISA controller are discrete. */
	ctlp->io_num = 1;
	ctlp->io_rid = malloc(sizeof(*(ctlp->io_rid)) * MAX_AIOPS_PER_BOARD, M_DEVBUF, M_NOWAIT | M_ZERO);
	ctlp->io = malloc(sizeof(*(ctlp->io)) * MAX_AIOPS_PER_BOARD, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (ctlp->io_rid == NULL || ctlp->io == NULL) {
		device_printf(dev, "rp_attach: Out of memory.\n");
		retval = ENOMEM;
		goto nogo;
	}

	ctlp->bus_ctlp = malloc(sizeof(ISACONTROLLER_t) * 1, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (ctlp->bus_ctlp == NULL) {
		device_printf(dev, "rp_attach: Out of memory.\n");
		retval = ENOMEM;
		goto nogo;
	}

	ctlp->io_rid[0] = 0;
	if (rp_controller != NULL) {
		controller = rp_controller;
		ctlp->io[0] = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &ctlp->io_rid[0], 0x40, RF_ACTIVE);
	} else {
		controller = rp_controller = ctlp;
		ctlp->io[0] = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &ctlp->io_rid[0], 0x44, RF_ACTIVE);
	}
	if (ctlp->io[0] == NULL) {
		device_printf(dev, "rp_attach: Resource not available.\n");
		retval = ENXIO;
		goto nogo;
	}

	num_aiops = sInitController(ctlp,
				controller,
				MAX_AIOPS_PER_BOARD, 0,
				FREQ_DIS, 0);
	if (num_aiops <= 0) {
		device_printf(dev, "board%d init failed.\n", unit);
		retval = ENXIO;
		goto nogo;
	}

	if (rp_controller == NULL)
		rp_controller = controller;
	rp_nisadevs++;

	device_set_desc(dev, "RocketPort ISA");

	return (0);

nogo:
	rp_isareleaseresource(ctlp);

	return (retval);
}