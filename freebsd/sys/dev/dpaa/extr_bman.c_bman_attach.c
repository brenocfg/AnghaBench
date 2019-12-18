#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Error ;
struct TYPE_6__ {int /*<<< orphan*/  minorRev; int /*<<< orphan*/  majorRev; } ;
typedef  TYPE_1__ t_BmRevisionInfo ;
struct TYPE_7__ {int totalNumOfBuffers; uintptr_t errIrq; int /*<<< orphan*/  partNumOfPools; scalar_t__ partBpidBase; struct bman_softc* h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  baseAddress; int /*<<< orphan*/  guestId; } ;
typedef  TYPE_2__ t_BmParam ;
struct bman_softc {int /*<<< orphan*/ * sc_bh; int /*<<< orphan*/ * sc_ires; int /*<<< orphan*/ * sc_rres; scalar_t__ sc_irid; int /*<<< orphan*/  sc_dev; scalar_t__ sc_rrid; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bp ;

/* Variables and functions */
 int /*<<< orphan*/  BMAN_CCSR_SIZE ; 
 int BMAN_MAX_BUFFERS ; 
 int /*<<< orphan*/ * BM_Config (TYPE_2__*) ; 
 scalar_t__ BM_ConfigFbprThreshold (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BM_GetRevision (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ BM_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BM_MAX_NUM_OF_POOLS ; 
 int ENXIO ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  NCSW_MASTER_ID ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ XX_MallocSmartInit () ; 
 int /*<<< orphan*/  bman_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bman_exception ; 
 struct bman_softc* bman_sc ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct bman_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 

int
bman_attach(device_t dev)
{
	struct bman_softc *sc;
	t_BmRevisionInfo rev;
	t_Error error;
	t_BmParam bp;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	bman_sc = sc;

	/* Check if MallocSmart allocator is ready */
	if (XX_MallocSmartInit() != E_OK)
		return (ENXIO);

	/* Allocate resources */
	sc->sc_rrid = 0;
	sc->sc_rres = bus_alloc_resource_anywhere(dev, SYS_RES_MEMORY,
	    &sc->sc_rrid, BMAN_CCSR_SIZE, RF_ACTIVE);
	if (sc->sc_rres == NULL)
		return (ENXIO);

	sc->sc_irid = 0;
	sc->sc_ires = bus_alloc_resource_any(sc->sc_dev, SYS_RES_IRQ,
	    &sc->sc_irid, RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_ires == NULL)
		goto err;

	/* Initialize BMAN */
	memset(&bp, 0, sizeof(bp));
	bp.guestId = NCSW_MASTER_ID;
	bp.baseAddress = rman_get_bushandle(sc->sc_rres);
	bp.totalNumOfBuffers = BMAN_MAX_BUFFERS;
	bp.f_Exception = bman_exception;
	bp.h_App = sc;
	bp.errIrq = (uintptr_t)sc->sc_ires;
	bp.partBpidBase = 0;
	bp.partNumOfPools = BM_MAX_NUM_OF_POOLS;

	sc->sc_bh = BM_Config(&bp);
	if (sc->sc_bh == NULL)
		goto err;

	/* Warn if there is less than 5% free FPBR's in pool */
	error = BM_ConfigFbprThreshold(sc->sc_bh, (BMAN_MAX_BUFFERS / 8) / 20);
	if (error != E_OK)
		goto err;

	error = BM_Init(sc->sc_bh);
	if (error != E_OK)
		goto err;

	error = BM_GetRevision(sc->sc_bh, &rev);
	if (error != E_OK)
		goto err;

	device_printf(dev, "Hardware version: %d.%d.\n",
	    rev.majorRev, rev.minorRev);

	return (0);

err:
	bman_detach(dev);
	return (ENXIO);
}