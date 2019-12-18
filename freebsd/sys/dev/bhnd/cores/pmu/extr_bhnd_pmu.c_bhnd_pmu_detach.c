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
struct bhnd_pmu_softc {int /*<<< orphan*/  chipc_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  clkctl; int /*<<< orphan*/  query; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_SERVICE_ANY ; 
 int /*<<< orphan*/  BHND_SERVICE_CHIPC ; 
 int /*<<< orphan*/  BPMU_LOCK_DESTROY (struct bhnd_pmu_softc*) ; 
 int bhnd_deregister_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_free_core_clkctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_pmu_query_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_release_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
bhnd_pmu_detach(device_t dev)
{
	struct bhnd_pmu_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	if ((error = bhnd_deregister_provider(dev, BHND_SERVICE_ANY)))
		return (error);

	BPMU_LOCK_DESTROY(sc);
	bhnd_pmu_query_fini(&sc->query);
	bhnd_free_core_clkctl(sc->clkctl);
	bhnd_release_provider(sc->dev, sc->chipc_dev, BHND_SERVICE_CHIPC);
	
	return (0);
}