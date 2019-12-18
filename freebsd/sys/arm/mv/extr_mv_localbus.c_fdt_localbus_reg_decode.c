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
typedef  scalar_t__ u_long ;
struct localbus_softc {TYPE_1__* sc_banks; int /*<<< orphan*/  sc_dev; } ;
struct localbus_devinfo {int di_bank; int /*<<< orphan*/  di_res; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ va; int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int ENXIO ; 
 int MV_LOCALBUS_MAX_BANKS ; 
 int OF_getprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  debugf (char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 int fdt_data_get (void*,int) ; 
 int fdt_data_to_res (int*,int,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fdt_localbus_reg_decode(phandle_t node, struct localbus_softc *sc,
    struct localbus_devinfo *di)
{
	u_long start, end, count;
	pcell_t *reg, *regptr;
	pcell_t addr_cells, size_cells;
	int tuple_size, tuples;
	int i, rv, bank;

	if (fdt_addrsize_cells(OF_parent(node), &addr_cells, &size_cells) != 0)
		return (ENXIO);

	tuple_size = sizeof(pcell_t) * (addr_cells + size_cells);
	tuples = OF_getprop_alloc_multi(node, "reg", tuple_size, (void **)&reg);
	debugf("addr_cells = %d, size_cells = %d\n", addr_cells, size_cells);
	debugf("tuples = %d, tuple size = %d\n", tuples, tuple_size);
	if (tuples <= 0)
		/* No 'reg' property in this node. */
		return (0);

	regptr = reg;
	for (i = 0; i < tuples; i++) {

		bank = fdt_data_get((void *)regptr, 1);

		if (bank >= MV_LOCALBUS_MAX_BANKS) {
			device_printf(sc->sc_dev, "bank number [%d] out of "
			    "range\n", bank);
			continue;
		}

		/*
		 * If device doesn't have virtual to physical mapping don't add
		 * resources
		 */
		if (!(sc->sc_banks[bank].mapped)) {
			device_printf(sc->sc_dev, "device [%d]: missing memory "
			    "mapping\n", bank);
			continue;
		}

		di->di_bank = bank;
		regptr += 1;

		/* Get address/size. */
		rv = fdt_data_to_res(regptr, addr_cells - 1, size_cells, &start,
		    &count);
		if (rv != 0) {
			resource_list_free(&di->di_res);
			goto out;
		}

		/* Check if enough amount of memory is mapped */
		if (sc->sc_banks[bank].size < count) {
			device_printf(sc->sc_dev, "device [%d]: not enough "
			    "memory reserved\n", bank);
			continue;
		}

		regptr += addr_cells - 1 + size_cells;

		/* Calculate address range relative to VA base. */
		start = sc->sc_banks[bank].va + start;
		end = start + count - 1;

		debugf("reg addr bank = %d, start = %lx, end = %lx, "
		    "count = %lx\n", bank, start, end, count);

		/* Use bank (CS) cell as rid. */
		resource_list_add(&di->di_res, SYS_RES_MEMORY, di->di_bank,
		    start, end, count);
	}
	rv = 0;
out:
	OF_prop_free(reg);
	return (rv);
}