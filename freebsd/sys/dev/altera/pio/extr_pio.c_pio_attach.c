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
struct pio_softc {void* dev; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct fdt_ic {int iph; void* dev; } ;
typedef  int phandle_t ;
typedef  void* device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct fdt_ic*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pio_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  fdt_ic_list_head ; 
 int /*<<< orphan*/  fdt_ics ; 
 struct fdt_ic* malloc (int,int /*<<< orphan*/ ,int) ; 
 int ofw_bus_get_node (void*) ; 
 int /*<<< orphan*/  pio_spec ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pio_attach(device_t dev)
{
	struct pio_softc *sc;
	struct fdt_ic *fic;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, pio_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	fic = malloc(sizeof(*fic), M_DEVBUF, M_WAITOK|M_ZERO);
	fic->iph = node;
	fic->dev = dev;
	SLIST_INSERT_HEAD(&fdt_ic_list_head, fic, fdt_ics);

	return (0);
}