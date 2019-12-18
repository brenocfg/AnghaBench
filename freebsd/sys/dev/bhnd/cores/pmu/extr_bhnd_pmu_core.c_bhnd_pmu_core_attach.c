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
struct bhnd_resource {int dummy; } ;
struct bhnd_pmu_softc {int rid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_alloc_pmu (int /*<<< orphan*/ ) ; 
 struct bhnd_resource* bhnd_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bhnd_pmu_attach (int /*<<< orphan*/ ,struct bhnd_resource*) ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct bhnd_resource*) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
bhnd_pmu_core_attach(device_t dev)
{
	struct bhnd_pmu_softc	*sc;
	struct bhnd_resource	*res;
	int			 error;
	int			 rid;

	sc = device_get_softc(dev);

	/* Allocate register block */
	rid = 0;
	res = bhnd_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (res == NULL) {
		device_printf(dev, "failed to allocate resources\n");
		return (ENXIO);
	}

	/* Allocate our per-core PMU state */
	if ((error = bhnd_alloc_pmu(dev))) {
		device_printf(sc->dev, "failed to allocate PMU state: %d\n",
		    error);

		return (error);
	}

	/* Delegate to common driver implementation */
	if ((error = bhnd_pmu_attach(dev, res))) {
		bhnd_release_resource(dev, SYS_RES_MEMORY, rid, res);
		return (error);
	}

	sc->rid = rid;
	return (0);
}