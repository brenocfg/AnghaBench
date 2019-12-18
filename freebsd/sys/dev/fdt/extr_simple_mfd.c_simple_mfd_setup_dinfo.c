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
struct simplebus_softc {int /*<<< orphan*/  scells; int /*<<< orphan*/  acells; } ;
struct simplebus_devinfo {int /*<<< orphan*/  rl; int /*<<< orphan*/  obdinfo; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 struct simplebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct simplebus_devinfo*,int /*<<< orphan*/ ) ; 
 struct simplebus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_reg_to_rl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

struct simplebus_devinfo *
simple_mfd_setup_dinfo(device_t dev, phandle_t node,
    struct simplebus_devinfo *di)
{
	struct simplebus_softc *sc;
	struct simplebus_devinfo *ndi;

	sc = device_get_softc(dev);
	if (di == NULL)
		ndi = malloc(sizeof(*ndi), M_DEVBUF, M_WAITOK | M_ZERO);
	else
		ndi = di;
	if (ofw_bus_gen_setup_devinfo(&ndi->obdinfo, node) != 0) {
		if (di == NULL)
			free(ndi, M_DEVBUF);
		return (NULL);
	}

	/* reg resources is from the parent but interrupts is on the node itself */
	resource_list_init(&ndi->rl);
	ofw_bus_reg_to_rl(dev, OF_parent(node), sc->acells, sc->scells, &ndi->rl);
	ofw_bus_intr_to_rl(dev, node, &ndi->rl, NULL);

	return (ndi);
}