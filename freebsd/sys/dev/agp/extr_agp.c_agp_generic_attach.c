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
typedef  unsigned int u_int ;
struct agp_softc {int as_aperture_rid; unsigned int as_maxmem; int as_nextid; TYPE_1__* as_devnode; int /*<<< orphan*/  as_memory; int /*<<< orphan*/  as_lock; int /*<<< orphan*/  as_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  si_drv1; } ;

/* Variables and functions */
 int AGP_APBASE ; 
 int AGP_MAX_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  agp_cdevsw ; 
 int /*<<< orphan*/  agp_devclass ; 
 unsigned int** agp_max ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realmem ; 

int
agp_generic_attach(device_t dev)
{
	struct agp_softc *sc = device_get_softc(dev);
	int i;
	u_int memsize;

	/*
	 * Find and map the aperture, RF_SHAREABLE for DRM but not RF_ACTIVE
	 * because the kernel doesn't need to map it.
	 */

	if (sc->as_aperture_rid != -1) {
		if (sc->as_aperture_rid == 0)
			sc->as_aperture_rid = AGP_APBASE;

		sc->as_aperture = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		    &sc->as_aperture_rid, RF_SHAREABLE);
		if (!sc->as_aperture)
			return ENOMEM;
	}

	/*
	 * Work out an upper bound for agp memory allocation. This
	 * uses a heurisitc table from the Linux driver.
	 */
	memsize = ptoa(realmem) >> 20;
	for (i = 0; i < AGP_MAX_SIZE; i++) {
		if (memsize <= agp_max[i][0])
			break;
	}
	if (i == AGP_MAX_SIZE)
		i = AGP_MAX_SIZE - 1;
	sc->as_maxmem = agp_max[i][1] << 20U;

	/*
	 * The lock is used to prevent re-entry to
	 * agp_generic_bind_memory() since that function can sleep.
	 */
	mtx_init(&sc->as_lock, "agp lock", NULL, MTX_DEF);

	/*
	 * Initialise stuff for the userland device.
	 */
	agp_devclass = devclass_find("agp");
	TAILQ_INIT(&sc->as_memory);
	sc->as_nextid = 1;

	sc->as_devnode = make_dev(&agp_cdevsw,
	    0, UID_ROOT, GID_WHEEL, 0600, "agpgart");
	sc->as_devnode->si_drv1 = dev;

	return 0;
}