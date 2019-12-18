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
typedef  void* vm_offset_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct uninorth_softc {int sc_ver; int sc_skipslot; int /*<<< orphan*/  sc_cfg_mtx; void* sc_data; void* sc_addr; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int cell_t ;
typedef  int /*<<< orphan*/  acells ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 struct uninorth_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_pci_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_mapdev (int,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
uninorth_attach(device_t dev)
{
	struct		uninorth_softc *sc;
	const char	*compatible;
	const char	*name;
	phandle_t	node;
	uint32_t	reg[3];
	uint64_t	regbase;
	cell_t		acells;
	int		unit;

	node = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);
	name = device_get_name(dev);
	unit = device_get_unit(dev);

	if (OF_getprop(node, "reg", reg, sizeof(reg)) < 8)
		return (ENXIO);

	sc->sc_ver = 0;
	compatible = ofw_bus_get_compat(dev);
	if (strcmp(compatible, "u3-agp") == 0)
		sc->sc_ver = 3;
	if (strcmp(compatible, "u4-pcie") == 0)
		sc->sc_ver = 4;

	acells = 1;
	OF_getprop(OF_parent(node), "#address-cells", &acells, sizeof(acells));

	regbase = reg[0];
	if (acells == 2) {
		regbase <<= 32;
		regbase |= reg[1];
	}

	sc->sc_addr = (vm_offset_t)pmap_mapdev(regbase + 0x800000, PAGE_SIZE);
	sc->sc_data = (vm_offset_t)pmap_mapdev(regbase + 0xc00000, PAGE_SIZE);

	if (resource_int_value(name, unit, "skipslot", &sc->sc_skipslot) != 0)
		sc->sc_skipslot = -1;

	mtx_init(&sc->sc_cfg_mtx, "uninorth pcicfg", NULL, MTX_SPIN);

	return (ofw_pci_attach(dev));
}