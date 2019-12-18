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
struct bhnd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bhnd_get_pmu_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct bhnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

void
bhnd_generic_child_deleted(device_t dev, device_t child)
{
	struct bhnd_softc	*sc;

	sc = device_get_softc(dev);

	/* Free device info */
	if (bhnd_get_pmu_info(child) != NULL) {
		/* Releasing PMU requests automatically would be nice,
		 * but we can't reference per-core PMU register
		 * resource after driver detach */
		panic("%s leaked device pmu state\n",
		    device_get_nameunit(child));
	}
}