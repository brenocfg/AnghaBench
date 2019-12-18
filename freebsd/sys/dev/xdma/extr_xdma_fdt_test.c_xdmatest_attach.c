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
struct TYPE_2__ {struct xdmatest_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct xdmatest_softc {TYPE_1__ config_intrhook; int /*<<< orphan*/  dev; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct xdmatest_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xdmatest_alloc_test_memory (struct xdmatest_softc*) ; 
 int /*<<< orphan*/  xdmatest_delayed_attach ; 

__attribute__((used)) static int
xdmatest_attach(device_t dev)
{
	struct xdmatest_softc *sc;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->mtx, device_get_nameunit(dev), "xdmatest", MTX_DEF);

	/* Allocate test memory */
	err = xdmatest_alloc_test_memory(sc);
	if (err != 0) {
		device_printf(sc->dev, "Can't allocate test memory.\n");
		return (-1);
	}

	/* We'll run test later, but before / mount. */
	sc->config_intrhook.ich_func = xdmatest_delayed_attach;
	sc->config_intrhook.ich_arg = sc;
	if (config_intrhook_establish(&sc->config_intrhook) != 0)
		device_printf(dev, "config_intrhook_establish failed\n");

	return (0);
}