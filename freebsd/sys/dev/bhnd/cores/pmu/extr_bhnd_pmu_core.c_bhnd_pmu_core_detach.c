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
struct bhnd_pmu_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_pmu_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pmu_core_detach(device_t dev)
{
	struct bhnd_pmu_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);
	
	/* Delegate to common driver implementation */
	if ((error = bhnd_pmu_detach(dev)))
		return (error);

	bhnd_release_resource(dev, SYS_RES_MEMORY, sc->rid, sc->res);
	return (0);
}