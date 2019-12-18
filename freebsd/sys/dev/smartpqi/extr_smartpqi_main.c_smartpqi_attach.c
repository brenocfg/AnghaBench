#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_7__ {int pqi_hwif; int /*<<< orphan*/ * pqi_regs_res0; int /*<<< orphan*/  pqi_regs_rid0; int /*<<< orphan*/  pqi_dev; int /*<<< orphan*/  event_task; int /*<<< orphan*/  eh; int /*<<< orphan*/  wellness_periodic; int /*<<< orphan*/  pqi_buffer_dmat; int /*<<< orphan*/  map_lock; int /*<<< orphan*/  pqi_parent_dmat; int /*<<< orphan*/  mtx_init; int /*<<< orphan*/  cam_lock; int /*<<< orphan*/  sim_registered; } ;
struct TYPE_6__ {int max_sg_elem; int max_outstanding_io; } ;
struct TYPE_5__ {int /*<<< orphan*/  pqi_bhandle; int /*<<< orphan*/  pqi_btag; } ;
struct pqisrc_softstate {char* pci_mem_base_vaddr; char* os_name; TYPE_3__ os_specific; TYPE_2__ pqi_cap; TYPE_4__* rcb; TYPE_1__ pci_mem_handle; } ;
struct pqi_ident {int hwif; } ;
struct TYPE_8__ {int /*<<< orphan*/  cm_datamap; } ;
typedef  TYPE_4__ rcb_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int /*<<< orphan*/  DBG_INFO (char*,struct pqisrc_softstate*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pqisrc_softstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PAGE_SIZE ; 
 int PCIM_CMD_MEMEN ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
#define  PQI_HWIF_SRCV 128 
 int PQI_HWIF_UNKNOWN ; 
 int PQI_STATUS_FAILURE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int create_char_dev (struct pqisrc_softstate*,int) ; 
 struct pqisrc_softstate* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  memset (struct pqisrc_softstate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_start_heartbeat_timer (void*) ; 
 int /*<<< orphan*/  os_wellness_periodic ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pqi_ident* pqi_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_event_worker ; 
 int pqisrc_init (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  pqisrc_save_controller_info (struct pqisrc_softstate*) ; 
 int pqisrc_scan_devices (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int register_sim (struct pqisrc_softstate*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  smartpqi_shutdown ; 
 int /*<<< orphan*/  smartpqi_target_rescan (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,struct pqisrc_softstate*,int) ; 

__attribute__((used)) static int
smartpqi_attach(device_t dev)
{
	struct pqisrc_softstate *softs = NULL;
	struct pqi_ident *id = NULL;
	int error = 0;
	u_int32_t command = 0, i = 0;
	int card_index = device_get_unit(dev);
	rcb_t *rcbp = NULL;

	/*
	 * Initialise softc.
	 */
	softs = device_get_softc(dev);

	if (!softs) {
		printf("Could not get softc\n");
		error = EINVAL;
		goto out;
	}
	memset(softs, 0, sizeof(*softs));
	softs->os_specific.pqi_dev = dev;

	DBG_FUNC("IN\n");

	/* assume failure is 'not configured' */
	error = ENXIO;

	/* 
	 * Verify that the adapter is correctly set up in PCI space.
	 */
	pci_enable_busmaster(softs->os_specific.pqi_dev);
	command = pci_read_config(softs->os_specific.pqi_dev, PCIR_COMMAND, 2);
	if ((command & PCIM_CMD_MEMEN) == 0) {
		DBG_ERR("memory window not available command = %d\n", command);
		error = ENXIO;
		goto out;
	}

	/* 
	 * Detect the hardware interface version, set up the bus interface
	 * indirection.
	 */
	id = pqi_find_ident(dev);
	softs->os_specific.pqi_hwif = id->hwif;

	switch(softs->os_specific.pqi_hwif) {
		case PQI_HWIF_SRCV:
			DBG_INFO("set hardware up for PMC SRCv for %p", softs);
			break;
		default:
			softs->os_specific.pqi_hwif = PQI_HWIF_UNKNOWN;
			DBG_ERR("unknown hardware type\n");
			error = ENXIO;
			goto out;
	}

	pqisrc_save_controller_info(softs);

	/*
	 * Allocate the PCI register window.
	 */
	softs->os_specific.pqi_regs_rid0 = PCIR_BAR(0);
	if ((softs->os_specific.pqi_regs_res0 =
		bus_alloc_resource_any(softs->os_specific.pqi_dev, SYS_RES_MEMORY,
		&softs->os_specific.pqi_regs_rid0, RF_ACTIVE)) == NULL) {
		DBG_ERR("couldn't allocate register window 0\n");
		/* assume failure is 'out of memory' */
		error = ENOMEM;
		goto out;
	}

	bus_get_resource_start(softs->os_specific.pqi_dev, SYS_RES_MEMORY,
		softs->os_specific.pqi_regs_rid0);

	softs->pci_mem_handle.pqi_btag = rman_get_bustag(softs->os_specific.pqi_regs_res0);
	softs->pci_mem_handle.pqi_bhandle = rman_get_bushandle(softs->os_specific.pqi_regs_res0);
	/* softs->pci_mem_base_vaddr = (uintptr_t)rman_get_virtual(softs->os_specific.pqi_regs_res0); */
	softs->pci_mem_base_vaddr = (char *)rman_get_virtual(softs->os_specific.pqi_regs_res0);

	/*
	 * Allocate the parent bus DMA tag appropriate for our PCI interface.
	 * 
	 * Note that some of these controllers are 64-bit capable.
	 */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 	/* parent */
				PAGE_SIZE, 0,		/* algnmnt, boundary */
				BUS_SPACE_MAXADDR_32BIT,/* lowaddr */
				BUS_SPACE_MAXADDR, 	/* highaddr */
				NULL, NULL, 		/* filter, filterarg */
				BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
				BUS_SPACE_UNRESTRICTED,	/* nsegments */
				BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
				0,			/* flags */
				NULL, NULL,		/* No locking needed */
				&softs->os_specific.pqi_parent_dmat)) {
		DBG_ERR("can't allocate parent DMA tag\n");
		/* assume failure is 'out of memory' */
		error = ENOMEM;
		goto dma_out;
	}

	softs->os_specific.sim_registered = FALSE;
	softs->os_name = "FreeBSD ";
	
	/* Initialize the PQI library */
	error = pqisrc_init(softs);
	if (error) {
		DBG_ERR("Failed to initialize pqi lib error = %d\n", error);
		error = PQI_STATUS_FAILURE;
		goto out;
	}

        mtx_init(&softs->os_specific.cam_lock, "cam_lock", NULL, MTX_DEF);
        softs->os_specific.mtx_init = TRUE;
        mtx_init(&softs->os_specific.map_lock, "map_lock", NULL, MTX_DEF);

        /*
         * Create DMA tag for mapping buffers into controller-addressable space.
         */
        if (bus_dma_tag_create(softs->os_specific.pqi_parent_dmat,/* parent */
				1, 0,			/* algnmnt, boundary */
				BUS_SPACE_MAXADDR_32BIT,/* lowaddr */
				BUS_SPACE_MAXADDR,	/* highaddr */
				NULL, NULL,		/* filter, filterarg */
				softs->pqi_cap.max_sg_elem*PAGE_SIZE,/*maxsize*/
				softs->pqi_cap.max_sg_elem,	/* nsegments */
				BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
				BUS_DMA_ALLOCNOW,		/* flags */
				busdma_lock_mutex,		/* lockfunc */
				&softs->os_specific.map_lock,	/* lockfuncarg*/
				&softs->os_specific.pqi_buffer_dmat)) {
		DBG_ERR("can't allocate buffer DMA tag for pqi_buffer_dmat\n");
		return (ENOMEM);
        }

	rcbp = &softs->rcb[1];
	for( i = 1;  i <= softs->pqi_cap.max_outstanding_io; i++, rcbp++ ) {
		if ((error = bus_dmamap_create(softs->os_specific.pqi_buffer_dmat, 0, &rcbp->cm_datamap)) != 0) {
			DBG_ERR("Cant create datamap for buf @"
			"rcbp = %p maxio = %d error = %d\n", 
			rcbp, softs->pqi_cap.max_outstanding_io, error);
			goto dma_out;
		}
	}

	os_start_heartbeat_timer((void *)softs); /* Start the heart-beat timer */
	softs->os_specific.wellness_periodic = timeout( os_wellness_periodic, 
							softs, 120*hz);
	/* Register our shutdown handler. */
	softs->os_specific.eh = EVENTHANDLER_REGISTER(shutdown_final, 
				smartpqi_shutdown, softs, SHUTDOWN_PRI_DEFAULT);

	error = pqisrc_scan_devices(softs);
	if (error) {
		DBG_ERR("Failed to scan lib error = %d\n", error);
		error = PQI_STATUS_FAILURE;
		goto out;
	}

	error = register_sim(softs, card_index);
	if (error) {
		DBG_ERR("Failed to register sim index = %d error = %d\n", 
			card_index, error);
		goto out;
	}

	smartpqi_target_rescan(softs);		

	TASK_INIT(&softs->os_specific.event_task, 0, pqisrc_event_worker,softs);

	error = create_char_dev(softs, card_index);
	if (error) {
		DBG_ERR("Failed to register character device index=%d r=%d\n", 
			card_index, error);
		goto out;
	}
	goto out;

dma_out:
	if (softs->os_specific.pqi_regs_res0 != NULL)
		bus_release_resource(softs->os_specific.pqi_dev, SYS_RES_MEMORY,
			softs->os_specific.pqi_regs_rid0, 
			softs->os_specific.pqi_regs_res0);
out:
	DBG_FUNC("OUT error = %d\n", error);
	return(error);
}