#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_ports; int /*<<< orphan*/ ** ifname; int /*<<< orphan*/ ** ifp; int /*<<< orphan*/ ** miibus; int /*<<< orphan*/  sx; } ;
typedef  TYPE_1__ e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_E6000SW ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
e6000sw_detach(device_t dev)
{
	int phy;
	e6000sw_softc_t *sc;

	sc = device_get_softc(dev);
	bus_generic_detach(dev);
	sx_destroy(&sc->sx);
	for (phy = 0; phy < sc->num_ports; phy++) {
		if (sc->miibus[phy] != NULL)
			device_delete_child(dev, sc->miibus[phy]);
		if (sc->ifp[phy] != NULL)
			if_free(sc->ifp[phy]);
		if (sc->ifname[phy] != NULL)
			free(sc->ifname[phy], M_E6000SW);
	}

	return (0);
}