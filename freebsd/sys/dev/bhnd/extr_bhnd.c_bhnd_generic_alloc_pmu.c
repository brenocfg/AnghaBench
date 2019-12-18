#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct resource_list {int dummy; } ;
struct bhnd_softc {int /*<<< orphan*/  dev; } ;
struct bhnd_resource {int direct; int /*<<< orphan*/ * res; } ;
struct bhnd_core_clkctl {int dummy; } ;
typedef  scalar_t__ device_t ;
typedef  int bus_size_t ;
typedef  int bhnd_size_t ;
typedef  int bhnd_addr_t ;

/* Variables and functions */
 int BHND_CLK_CTL_ST ; 
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int /*<<< orphan*/  BHND_SERVICE_PMU ; 
 struct resource_list* BUS_GET_RESOURCE_LIST (scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct bhnd_core_clkctl* bhnd_alloc_core_clkctl (scalar_t__,scalar_t__,struct bhnd_resource*,int,int /*<<< orphan*/ ) ; 
 struct bhnd_core_clkctl* bhnd_get_pmu_info (scalar_t__) ; 
 int bhnd_get_region_addr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  bhnd_pmu_get_max_transition_latency (scalar_t__) ; 
 int /*<<< orphan*/  bhnd_release_provider (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_retain_provider (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_set_pmu_info (scalar_t__,struct bhnd_core_clkctl*) ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct bhnd_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  free (struct bhnd_resource*,int /*<<< orphan*/ ) ; 
 struct bhnd_resource* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_get_end (int /*<<< orphan*/ *) ; 
 int rman_get_flags (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 

int
bhnd_generic_alloc_pmu(device_t dev, device_t child)
{
	struct bhnd_softc		*sc;
	struct bhnd_resource		*r;
	struct bhnd_core_clkctl		*clkctl;
	struct resource_list		*rl;
	struct resource_list_entry	*rle;
	device_t			 pmu_dev;
	bhnd_addr_t			 r_addr;
	bhnd_size_t			 r_size;
	bus_size_t			 pmu_regs;
	u_int				 max_latency;
	int				 error;

	GIANT_REQUIRED;	/* for newbus */

	if (device_get_parent(child) != dev)
		return (EINVAL);

	sc = device_get_softc(dev);
	clkctl = bhnd_get_pmu_info(child);
	pmu_regs = BHND_CLK_CTL_ST;

	/* already allocated? */
	if (clkctl != NULL) {
		panic("duplicate PMU allocation for %s",
		    device_get_nameunit(child));
	}

	/* Determine address+size of the core's PMU register block */
	error = bhnd_get_region_addr(child, BHND_PORT_DEVICE, 0, 0, &r_addr,
	    &r_size);
	if (error) {
		device_printf(sc->dev, "error fetching register block info for "
		    "%s: %d\n", device_get_nameunit(child), error);
		return (error);
	}

	if (r_size < (pmu_regs + sizeof(uint32_t))) {
		device_printf(sc->dev, "pmu offset %#jx would overrun %s "
		    "register block\n", (uintmax_t)pmu_regs,
		    device_get_nameunit(child));
		return (ENODEV);
	}

	/* Locate actual resource containing the core's register block */
	if ((rl = BUS_GET_RESOURCE_LIST(dev, child)) == NULL) {
		device_printf(dev, "NULL resource list returned for %s\n",
		    device_get_nameunit(child));
		return (ENXIO);
	}

	if ((rle = resource_list_find(rl, SYS_RES_MEMORY, 0)) == NULL) {
		device_printf(dev, "cannot locate core register resource "
		    "for %s\n", device_get_nameunit(child));
		return (ENXIO);
	}

	if (rle->res == NULL) {
		device_printf(dev, "core register resource unallocated for "
		    "%s\n", device_get_nameunit(child));
		return (ENXIO);
	}

	if (r_addr+pmu_regs < rman_get_start(rle->res) ||
	    r_addr+pmu_regs >= rman_get_end(rle->res))
	{
		device_printf(dev, "core register resource does not map PMU "
		    "registers at %#jx\n for %s\n", r_addr+pmu_regs,
		    device_get_nameunit(child));
		return (ENXIO);
	}

	/* Adjust PMU register offset relative to the actual start address
	 * of the core's register block allocation.
	 * 
	 * XXX: The saved offset will be invalid if bus_adjust_resource is
	 * used to modify the resource's start address.
	 */
	if (rman_get_start(rle->res) > r_addr)
		pmu_regs -= rman_get_start(rle->res) - r_addr;
	else
		pmu_regs -= r_addr - rman_get_start(rle->res);

	/* Retain a PMU reference for the clkctl instance state */
	pmu_dev = bhnd_retain_provider(child, BHND_SERVICE_PMU);
	if (pmu_dev == NULL) {
		device_printf(sc->dev, "PMU not found\n");
		return (ENXIO);
	}

	/* Fetch the maximum transition latency from our PMU */
	max_latency = bhnd_pmu_get_max_transition_latency(pmu_dev);

	/* Allocate a new bhnd_resource wrapping the standard resource we
	 * fetched from the resource list; we'll free this in
	 * bhnd_generic_release_pmu() */
	r = malloc(sizeof(struct bhnd_resource), M_BHND, M_NOWAIT);
	if (r == NULL) {
		bhnd_release_provider(child, pmu_dev, BHND_SERVICE_PMU);
		return (ENOMEM);
	}

	r->res = rle->res;
	r->direct = ((rman_get_flags(rle->res) & RF_ACTIVE) != 0);

	/* Allocate the clkctl instance */
	clkctl = bhnd_alloc_core_clkctl(child, pmu_dev, r, pmu_regs,
	    max_latency);
	if (clkctl == NULL) {
		free(r, M_BHND);
		bhnd_release_provider(child, pmu_dev, BHND_SERVICE_PMU);
		return (ENOMEM);
	}

	bhnd_set_pmu_info(child, clkctl);
	return (0);
}