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
struct lbc_softc {TYPE_1__* sc_banks; } ;
struct lbc_devinfo {int di_bank; int /*<<< orphan*/  di_res; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
struct TYPE_2__ {int kva; } ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  debugf (char*,int,int,...) ; 
 scalar_t__ fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 int fdt_data_get (void*,int) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
fdt_lbc_reg_decode(phandle_t node, struct lbc_softc *sc,
    struct lbc_devinfo *di)
{
	rman_res_t start, end, count;
	pcell_t *reg, *regptr;
	pcell_t addr_cells, size_cells;
	int tuple_size, tuples;
	int i, j, rv, bank;

	if (fdt_addrsize_cells(OF_parent(node), &addr_cells, &size_cells) != 0)
		return (ENXIO);

	tuple_size = sizeof(pcell_t) * (addr_cells + size_cells);
	tuples = OF_getencprop_alloc_multi(node, "reg", tuple_size,
	    (void **)&reg);
	debugf("addr_cells = %d, size_cells = %d\n", addr_cells, size_cells);
	debugf("tuples = %d, tuple size = %d\n", tuples, tuple_size);
	if (tuples <= 0)
		/* No 'reg' property in this node. */
		return (0);

	regptr = reg;
	for (i = 0; i < tuples; i++) {

		bank = fdt_data_get((void *)reg, 1);
		di->di_bank = bank;
		reg += 1;

		/* Get address/size. */
		start = count = 0;
		for (j = 0; j < addr_cells; j++) {
			start <<= 32;
			start |= reg[j];
		}
		for (j = 0; j < size_cells; j++) {
			count <<= 32;
			count |= reg[addr_cells + j - 1];
		}
		reg += addr_cells - 1 + size_cells;

		/* Calculate address range relative to VA base. */
		start = sc->sc_banks[bank].kva + start;
		end = start + count - 1;

		debugf("reg addr bank = %d, start = %jx, end = %jx, "
		    "count = %jx\n", bank, start, end, count);

		/* Use bank (CS) cell as rid. */
		resource_list_add(&di->di_res, SYS_RES_MEMORY, bank, start,
		    end, count);
	}
	rv = 0;
	OF_prop_free(regptr);
	return (rv);
}