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
struct tegra_lic_sc {int /*<<< orphan*/ ** mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct tegra_lic_sc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lic_spec ; 
 int nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_lic_detach(device_t dev)
{
	struct tegra_lic_sc *sc;
	int i;

	sc = device_get_softc(dev);
	for (i = 0; i < nitems(lic_spec); i++) {
		if (sc->mem_res[i] == NULL)
			continue;
		bus_release_resource(dev, SYS_RES_MEMORY, i,
		    sc->mem_res[i]);
	}
	return (0);
}