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
struct beri_mem_softc {TYPE_1__* mem_cdev; int /*<<< orphan*/ * res; int /*<<< orphan*/  mem_start; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct beri_mem_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  beri_mem_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct beri_mem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mem_cdevsw ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_mem_attach(device_t dev)
{
	struct beri_mem_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, beri_mem_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory info */
	sc->mem_size = rman_get_size(sc->res[0]);
	sc->mem_start = rman_get_start(sc->res[0]);

	sc->mem_cdev = make_dev(&mem_cdevsw, 0, UID_ROOT, GID_WHEEL,
	    0600, "beri_mem");

	if (sc->mem_cdev == NULL) {
		device_printf(dev, "Failed to create character device.\n");
		return (ENXIO);
	}

	sc->mem_cdev->si_drv1 = sc;

	return (0);
}