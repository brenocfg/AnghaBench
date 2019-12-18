#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct resource {int dummy; } ;
struct TYPE_9__ {scalar_t__ offset; } ;
struct TYPE_10__ {TYPE_4__ core; } ;
struct bhndb_regwin {scalar_t__ win_offset; TYPE_5__ d; } ;
struct TYPE_8__ {TYPE_2__* bus_res; } ;
struct bhndb_pci_softc {int /*<<< orphan*/  dev; TYPE_3__ bhndb; int /*<<< orphan*/  pci_devclass; } ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_7__ {int /*<<< orphan*/  res; TYPE_1__* cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  register_windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct resource* bhndb_host_resource_for_regwin (int /*<<< orphan*/ ,struct bhndb_regwin const*) ; 
 struct bhndb_regwin* bhndb_regwin_find_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bhndb_pci_get_core_regs(struct bhndb_pci_softc *sc, bus_size_t offset,
    bus_size_t size, struct resource **res, bus_size_t *res_offset)
{
	const struct bhndb_regwin	*win;
	struct resource			*r;

	/* Locate the static register window mapping the requested offset */
	win = bhndb_regwin_find_core(sc->bhndb.bus_res->cfg->register_windows,
	    sc->pci_devclass, 0, BHND_PORT_DEVICE, 0, 0, offset, size);
	if (win == NULL) {
		device_printf(sc->dev, "missing PCI core register window\n");
		return (ENXIO);
	}

	/* Fetch the resource containing the register window */
	r = bhndb_host_resource_for_regwin(sc->bhndb.bus_res->res, win);
	if (r == NULL) {
		device_printf(sc->dev, "missing PCI core register resource\n");
		return (ENXIO);
	}

	KASSERT(offset >= win->d.core.offset, ("offset %#jx outside of "
	    "register window", (uintmax_t)offset));

	*res = r;
	*res_offset = win->win_offset + (offset - win->d.core.offset);

	return (0);
}