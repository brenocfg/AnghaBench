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
struct sbus_softc {int sc_nrange; TYPE_1__* sc_rd; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  rd_rman; } ;

/* Variables and functions */
 int EINVAL ; 
 int SYS_RES_MEMORY ; 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rman_is_region_manager (struct resource*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sbus_adjust_resource(device_t bus, device_t child, int type,
    struct resource *r, rman_res_t start, rman_res_t end)
{
	struct sbus_softc *sc;
	int i;

	if (type == SYS_RES_MEMORY) {
		sc = device_get_softc(bus);
		for (i = 0; i < sc->sc_nrange; i++)
			if (rman_is_region_manager(r,
			    &sc->sc_rd[i].rd_rman) != 0)
				return (rman_adjust_resource(r, start, end));
		return (EINVAL);
	}
	return (bus_generic_adjust_resource(bus, child, type, r, start, end));
}