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
struct al_serdes_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int mode_set; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_serdes_spec ; 
 TYPE_1__* alpine_serdes_eth_group_mode ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct al_serdes_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static int
al_serdes_detach(device_t dev)
{
	struct al_serdes_softc *sc;

	sc = device_get_softc(dev);

	bus_release_resources(dev, al_serdes_spec, &sc->res);

	for (int i = 0; i < nitems(alpine_serdes_eth_group_mode); i++) {
		mtx_destroy(&alpine_serdes_eth_group_mode[i].lock);
		alpine_serdes_eth_group_mode[i].mode_set = false;
	}

	return (0);
}