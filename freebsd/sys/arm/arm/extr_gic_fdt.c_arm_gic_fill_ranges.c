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
struct TYPE_4__ {int nranges; TYPE_1__* ranges; } ;
struct arm_gic_fdt_softc {int addr_cells; int size_cells; TYPE_2__ base; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  host_cells ;
typedef  int cell_t ;
struct TYPE_3__ {int bus; int host; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_gic_fill_ranges(phandle_t node, struct arm_gic_fdt_softc *sc)
{
	pcell_t host_cells;
	cell_t *base_ranges;
	ssize_t nbase_ranges;
	int i, j, k;

	host_cells = 1;
	OF_getencprop(OF_parent(node), "#address-cells", &host_cells,
	    sizeof(host_cells));
	sc->addr_cells = 2;
	OF_getencprop(node, "#address-cells", &sc->addr_cells,
	    sizeof(sc->addr_cells));
	sc->size_cells = 2;
	OF_getencprop(node, "#size-cells", &sc->size_cells,
	    sizeof(sc->size_cells));

	nbase_ranges = OF_getproplen(node, "ranges");
	if (nbase_ranges < 0)
		return (-1);
	sc->base.nranges = nbase_ranges / sizeof(cell_t) /
	    (sc->addr_cells + host_cells + sc->size_cells);
	if (sc->base.nranges == 0)
		return (0);

	sc->base.ranges = malloc(sc->base.nranges * sizeof(sc->base.ranges[0]),
	    M_DEVBUF, M_WAITOK);
	base_ranges = malloc(nbase_ranges, M_DEVBUF, M_WAITOK);
	OF_getencprop(node, "ranges", base_ranges, nbase_ranges);

	for (i = 0, j = 0; i < sc->base.nranges; i++) {
		sc->base.ranges[i].bus = 0;
		for (k = 0; k < sc->addr_cells; k++) {
			sc->base.ranges[i].bus <<= 32;
			sc->base.ranges[i].bus |= base_ranges[j++];
		}
		sc->base.ranges[i].host = 0;
		for (k = 0; k < host_cells; k++) {
			sc->base.ranges[i].host <<= 32;
			sc->base.ranges[i].host |= base_ranges[j++];
		}
		sc->base.ranges[i].size = 0;
		for (k = 0; k < sc->size_cells; k++) {
			sc->base.ranges[i].size <<= 32;
			sc->base.ranges[i].size |= base_ranges[j++];
		}
	}

	free(base_ranges, M_DEVBUF);
	return (sc->base.nranges);
}