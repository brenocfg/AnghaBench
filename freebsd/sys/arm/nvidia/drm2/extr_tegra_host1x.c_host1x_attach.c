#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_drm {int dummy; } ;
struct host1x_softc {int /*<<< orphan*/ * mem_res; TYPE_2__* tegra_drm; int /*<<< orphan*/  clients; void* dev; } ;
typedef  void* device_t ;
struct TYPE_4__ {void* dev; TYPE_2__** dev_private; } ;
struct TYPE_5__ {TYPE_1__ drm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int ENXIO ; 
 int /*<<< orphan*/  LOCK_DESTROY (struct host1x_softc*) ; 
 int /*<<< orphan*/  LOCK_INIT (struct host1x_softc*) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (void*) ; 
 int /*<<< orphan*/  bus_release_resource (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct host1x_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
host1x_attach(device_t dev)
{
	int rv, rid;
	struct host1x_softc *sc;

	sc = device_get_softc(dev);
	sc->tegra_drm = malloc(sizeof(struct tegra_drm), DRM_MEM_DRIVER,
	    M_WAITOK | M_ZERO);

	/* crosslink together all worlds */
	sc->dev = dev;
	sc->tegra_drm->drm_dev.dev_private = &sc->tegra_drm;
	sc->tegra_drm->drm_dev.dev = dev;

	TAILQ_INIT(&sc->clients);

	LOCK_INIT(sc);

	/* Get the memory resource for the register mapping. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot map registers.\n");
		rv = ENXIO;
		goto fail;
	}

	return (bus_generic_attach(dev));

fail:
	if (sc->tegra_drm != NULL)
		free(sc->tegra_drm, DRM_MEM_DRIVER);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	LOCK_DESTROY(sc);
	return (rv);
}