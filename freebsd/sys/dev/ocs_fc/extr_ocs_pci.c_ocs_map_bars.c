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
struct ocs_softc {TYPE_1__* reg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * res; int /*<<< orphan*/  bhandle; int /*<<< orphan*/  btag; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_64BIT_BAR0 ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ocs_map_bars(device_t dev, struct ocs_softc *ocs)
{

	/*
	 * Map PCI BAR0 register into the CPU's space.
	 */

	ocs->reg[0].rid = PCIR_BAR(PCI_64BIT_BAR0);
	ocs->reg[0].res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
			&ocs->reg[0].rid, RF_ACTIVE);

	if (ocs->reg[0].res == NULL) {
		device_printf(dev, "bus_alloc_resource failed rid=%#x\n",
				ocs->reg[0].rid);
		return ENXIO;
	}

	ocs->reg[0].btag = rman_get_bustag(ocs->reg[0].res);
	ocs->reg[0].bhandle = rman_get_bushandle(ocs->reg[0].res);
	return 0;
}