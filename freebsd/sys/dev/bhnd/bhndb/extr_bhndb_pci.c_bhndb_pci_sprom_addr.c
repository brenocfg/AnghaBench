#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct bhndb_regwin {scalar_t__ win_offset; } ;
struct TYPE_4__ {TYPE_1__* bus_res; } ;
struct bhndb_pci_softc {TYPE_2__ bhndb; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct resource* bhndb_host_resource_for_regwin (int /*<<< orphan*/ ,struct bhndb_regwin const*) ; 
 struct bhndb_regwin* bhndb_pci_sprom_regwin (struct bhndb_pci_softc*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static bus_addr_t
bhndb_pci_sprom_addr(struct bhndb_pci_softc *sc)
{
	const struct bhndb_regwin	*sprom_win;
	struct resource			*r;

	/* Fetch the SPROM register window */
	sprom_win = bhndb_pci_sprom_regwin(sc);
	KASSERT(sprom_win != NULL, ("requested sprom address on PCI_V2+"));

	/* Fetch the associated resource */
	r = bhndb_host_resource_for_regwin(sc->bhndb.bus_res->res, sprom_win);
	KASSERT(r != NULL, ("missing resource for sprom window\n"));

	return (rman_get_start(r) + sprom_win->win_offset);
}