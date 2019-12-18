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
struct thunder_mdio_softc {int /*<<< orphan*/ * reg_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BASE_RID ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct thunder_mdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thunder_mdio_detach(device_t dev)
{
	struct thunder_mdio_softc *sc;

	sc = device_get_softc(dev);

	if (sc->reg_base != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, REG_BASE_RID,
		    sc->reg_base);
	}

	return (0);
}