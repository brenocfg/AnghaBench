#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hwrev; } ;
struct TYPE_7__ {int /*<<< orphan*/  obj; } ;
struct TYPE_9__ {int /*<<< orphan*/  eio; } ;
struct bcm_platform {int cfe_console; int cc_addr; int cc_caps; int cc_caps_ext; int pmu_addr; int cpu_addr; int /*<<< orphan*/  services; TYPE_2__ cpu_id; int /*<<< orphan*/  cid; int /*<<< orphan*/  pmu; TYPE_2__ pmu_id; TYPE_2__ cc_id; TYPE_1__ erom; TYPE_3__ erom_io; int /*<<< orphan*/  erom_ops; int /*<<< orphan*/  erom_impl; int /*<<< orphan*/ * nvram_cls; int /*<<< orphan*/ * nvram_io; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_10__ {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int BCM_CHIPC_READ_4 (struct bcm_platform*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_ERR (char*,int) ; 
 int /*<<< orphan*/  BCM_SOC_BSH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BCM_SOC_READ_4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFE_STDHANDLE_CONSOLE ; 
 int /*<<< orphan*/  CHIPC_CAP2_AOB ; 
 int /*<<< orphan*/  CHIPC_CAPABILITIES ; 
 int /*<<< orphan*/  CHIPC_CAPABILITIES_EXT ; 
 int /*<<< orphan*/  CHIPC_CAP_PMU ; 
 int CHIPC_GET_FLAG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CHIPC_HWREV_HAS_CAP_EXT (int /*<<< orphan*/ ) ; 
 TYPE_4__ bcm_cfe_nvram ; 
 int /*<<< orphan*/  bcm_chipc_cores ; 
 int /*<<< orphan*/  bcm_cpu0_cores ; 
 int bcm_erom_probe_and_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bcm_find_core (struct bcm_platform*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  bcm_get_bus_addr () ; 
 int /*<<< orphan*/  bcm_get_bus_size () ; 
 int bcm_nvram_find_cfedev (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int bcm_platform_data_avail ; 
 int /*<<< orphan*/  bcm_pmu_cores ; 
 int /*<<< orphan*/  bcm_pmu_soc_io ; 
 int /*<<< orphan*/  bhnd_erom_dump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_erom_io_fini (int /*<<< orphan*/ *) ; 
 int bhnd_erom_iobus_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_pmu_query_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcm_platform*) ; 
 int bhnd_service_registry_init (int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 int cfe_getstdhandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mips_bus_space_generic ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_init_platform_data(struct bcm_platform *bp)
{
	bus_addr_t		bus_addr, bus_size;
	bus_space_tag_t		erom_bst;
	bus_space_handle_t	erom_bsh;
	bool			aob, pmu;
	int			error;

	bus_addr = bcm_get_bus_addr();
	bus_size = bcm_get_bus_size();

#ifdef CFE
	/* Fetch CFE console handle (if any). Must be initialized before
	 * any calls to printf/early_putc. */
	if ((bp->cfe_console = cfe_getstdhandle(CFE_STDHANDLE_CONSOLE)) < 0)
		bp->cfe_console = -1;

	/* Probe CFE NVRAM sources */
	bp->nvram_io = &bcm_cfe_nvram.io;
	error = bcm_nvram_find_cfedev(&bcm_cfe_nvram, &bp->nvram_cls);
	if (error) {
		bp->nvram_io = NULL;
		bp->nvram_cls = NULL;
	}
#endif /* CFE */

	/* Probe and attach device table provider, populating our
	 * chip identification */
	erom_bst = mips_bus_space_generic;
	erom_bsh = BCM_SOC_BSH(bus_addr, 0);

	error = bhnd_erom_iobus_init(&bp->erom_io, bus_addr, bus_size, erom_bst,
	    erom_bsh);
	if (error) {
		BCM_ERR("failed to initialize erom I/O callbacks: %d\n", error);
		return (error);
	}

	error = bcm_erom_probe_and_attach(&bp->erom_impl, &bp->erom_ops,
	    &bp->erom.obj, sizeof(bp->erom), &bp->erom_io.eio, &bp->cid);
	if (error) {
		BCM_ERR("error attaching erom parser: %d\n", error);
		bhnd_erom_io_fini(&bp->erom_io.eio);
		return (error);
	}

	if (bootverbose)
		bhnd_erom_dump(&bp->erom.obj);

	/* Fetch chipcommon core info */
	error = bcm_find_core(bp, bcm_chipc_cores, nitems(bcm_chipc_cores),
	    &bp->cc_id, &bp->cc_addr);
	if (error) {
		BCM_ERR("error locating chipc core: %d\n", error);
		return (error);
	}

	/* Fetch chipc capability flags */
	bp->cc_caps = BCM_SOC_READ_4(bp->cc_addr, CHIPC_CAPABILITIES);
	bp->cc_caps_ext = 0x0;	

	if (CHIPC_HWREV_HAS_CAP_EXT(bp->cc_id.hwrev))
		bp->cc_caps_ext = BCM_CHIPC_READ_4(bp, CHIPC_CAPABILITIES_EXT);

	/* Fetch PMU info */
	pmu = CHIPC_GET_FLAG(bp->cc_caps, CHIPC_CAP_PMU);
	aob = CHIPC_GET_FLAG(bp->cc_caps_ext, CHIPC_CAP2_AOB);

	if (pmu && aob) {
		/* PMU block mapped to a PMU core on the Always-on-Bus (aob) */
		error = bcm_find_core(bp, bcm_pmu_cores, nitems(bcm_pmu_cores),
		    &bp->pmu_id,  &bp->pmu_addr);
		if (error) {
			BCM_ERR("error locating pmu core: %d\n", error);
			return (error);
		}
	} else if (pmu) {
		/* PMU block mapped to chipc */
		bp->pmu_addr = bp->cc_addr;
		bp->pmu_id = bp->cc_id;
	} else {
		/* No PMU */
		bp->pmu_addr = 0x0;
		memset(&bp->pmu_id, 0, sizeof(bp->pmu_id));
	}

	/* Initialize PMU query state */
	if (pmu) {
		error = bhnd_pmu_query_init(&bp->pmu, NULL, bp->cid,
		    &bcm_pmu_soc_io, bp);
		if (error) {
			BCM_ERR("bhnd_pmu_query_init() failed: %d\n", error);
			return (error);
		}
	}

	/* Find CPU core info */
	error = bcm_find_core(bp, bcm_cpu0_cores, nitems(bcm_cpu0_cores),
	    &bp->cpu_id,  &bp->cpu_addr);
	if (error) {
		BCM_ERR("error locating CPU core: %d\n", error);
		return (error);
	}

	/* Initialize our platform service registry */
	if ((error = bhnd_service_registry_init(&bp->services))) {
		BCM_ERR("error initializing service registry: %d\n", error);
		return (error);
	}

	bcm_platform_data_avail = true;
	return (0);
}