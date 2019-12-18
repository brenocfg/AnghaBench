#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct bhnd_resource {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_ctx; int /*<<< orphan*/  io; } ;
struct bhnd_pmu_softc {int /*<<< orphan*/ * chipc_dev; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * clkctl; TYPE_1__ query; struct bhnd_resource* res; int /*<<< orphan*/  io_ctx; int /*<<< orphan*/  io; int /*<<< orphan*/  cid; int /*<<< orphan*/  board; int /*<<< orphan*/  caps; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  scalar_t__ devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CLK_CTL_ST ; 
 int /*<<< orphan*/  BHND_PMU_CAP ; 
 int /*<<< orphan*/  BHND_PMU_MAX_TRANSITION_DLY ; 
 int /*<<< orphan*/  BHND_SERVICE_CHIPC ; 
 int /*<<< orphan*/  BHND_SERVICE_PMU ; 
 int /*<<< orphan*/  BPMU_LOCK_DESTROY (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BPMU_LOCK_INIT (struct bhnd_pmu_softc*) ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_UINT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/ * bhnd_alloc_core_clkctl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bhnd_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_bus_read_4 (struct bhnd_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_free_core_clkctl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_get_chipid (int /*<<< orphan*/ *) ; 
 int bhnd_pmu_init (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  bhnd_pmu_query_fini (TYPE_1__*) ; 
 int bhnd_pmu_query_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  bhnd_pmu_res_io ; 
 int /*<<< orphan*/  bhnd_pmu_sysctl_bus_freq ; 
 int /*<<< orphan*/  bhnd_pmu_sysctl_cpu_freq ; 
 int /*<<< orphan*/  bhnd_pmu_sysctl_mem_freq ; 
 int bhnd_read_board_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bhnd_register_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_release_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_retain_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 int device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ *) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 

int
bhnd_pmu_attach(device_t dev, struct bhnd_resource *res)
{
	struct bhnd_pmu_softc	*sc;
	struct sysctl_ctx_list	*ctx;
	struct sysctl_oid	*tree;
	devclass_t		 bhnd_class;
	device_t		 core, bus;
	int			 error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->res = res;

	/* Fetch capability flags */
	sc->caps = bhnd_bus_read_4(sc->res, BHND_PMU_CAP);

	/* Find the bus and bus-attached core */
	bhnd_class = devclass_find("bhnd");
	core = sc->dev;
	while ((bus = device_get_parent(core)) != NULL) {
		if (device_get_devclass(bus) == bhnd_class)
			break;

		core = bus;
	}

	if (core == NULL) {
		device_printf(sc->dev, "bhnd bus not found\n");
		return (ENXIO);
	}

	/* Fetch chip and board info */
	sc->cid = *bhnd_get_chipid(core);
	if ((error = bhnd_read_board_info(core, &sc->board))) {
		device_printf(sc->dev, "error fetching board info: %d\n",
		    error);
		return (ENXIO);
	}

	/* Initialize query state */
	error = bhnd_pmu_query_init(&sc->query, dev, sc->cid, &bhnd_pmu_res_io,
	    sc);
	if (error)
		return (error);
	sc->io = sc->query.io; 
	sc->io_ctx = sc->query.io_ctx;

	BPMU_LOCK_INIT(sc);

	/* Allocate our own core clkctl state directly; we use this to wait on
	 * PMU state transitions, avoiding a cyclic dependency between bhnd(4)'s
	 * clkctl handling and registration of this device as a PMU */
	sc->clkctl = bhnd_alloc_core_clkctl(core, dev, sc->res, BHND_CLK_CTL_ST,
	    BHND_PMU_MAX_TRANSITION_DLY);
	if (sc->clkctl == NULL) {
		device_printf(sc->dev, "failed to allocate clkctl for %s\n",
		    device_get_nameunit(core));
		error = ENOMEM;
		goto failed;
	}

	/* Locate ChipCommon device */
	sc->chipc_dev = bhnd_retain_provider(dev, BHND_SERVICE_CHIPC);
	if (sc->chipc_dev == NULL) {
		device_printf(sc->dev, "chipcommon device not found\n");
		error = ENXIO;
		goto failed;
	}

	/* Initialize PMU */
	if ((error = bhnd_pmu_init(sc))) {
		device_printf(sc->dev, "PMU init failed: %d\n", error);
		goto failed;
	}

	/* Register ourselves with the bus */
	if ((error = bhnd_register_provider(dev, BHND_SERVICE_PMU))) {
		device_printf(sc->dev, "failed to register PMU with bus : %d\n",
		    error);
		goto failed;
	}

	/* Set up sysctl nodes */
	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "bus_freq", CTLTYPE_UINT | CTLFLAG_RD, sc, 0,
	    bhnd_pmu_sysctl_bus_freq, "IU", "Bus clock frequency");

	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "cpu_freq", CTLTYPE_UINT | CTLFLAG_RD, sc, 0,
	    bhnd_pmu_sysctl_cpu_freq, "IU", "CPU clock frequency");
	
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "mem_freq", CTLTYPE_UINT | CTLFLAG_RD, sc, 0,
	    bhnd_pmu_sysctl_mem_freq, "IU", "Memory clock frequency");

	return (0);

failed:
	BPMU_LOCK_DESTROY(sc);
	bhnd_pmu_query_fini(&sc->query);

	if (sc->clkctl != NULL)
		bhnd_free_core_clkctl(sc->clkctl);

	if (sc->chipc_dev != NULL) {
		bhnd_release_provider(sc->dev, sc->chipc_dev,
		    BHND_SERVICE_CHIPC);
	}

	return (error);
}