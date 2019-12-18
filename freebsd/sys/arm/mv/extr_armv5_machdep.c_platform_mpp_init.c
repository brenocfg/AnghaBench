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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  pinmap ;
typedef  int /*<<< orphan*/  pin_count ;
typedef  int /*<<< orphan*/  pin_cells ;
typedef  int phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  mpp ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int ERANGE ; 
 int MPP_PINS_PER_REG ; 
 int MPP_PIN_CELLS ; 
 int MPP_PIN_MAX ; 
 int MPP_SEL (int,int) ; 
 int OF_finddevice (char*) ; 
 int OF_getencprop (int,char*,int*,int) ; 
 int OF_getprop (int,char*,int*,int) ; 
 int /*<<< orphan*/  OF_parent (int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 int fdt_data_to_res (int*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fdt_find_compatible (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_immr_va ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 scalar_t__ ofw_bus_node_is_compatible (int,char*) ; 

__attribute__((used)) static int
platform_mpp_init(void)
{
	pcell_t pinmap[MPP_PIN_MAX * MPP_PIN_CELLS];
	int mpp[MPP_PIN_MAX];
	uint32_t ctrl_val, ctrl_offset;
	pcell_t reg[4];
	u_long start, size;
	phandle_t node;
	pcell_t pin_cells, *pinmap_ptr, pin_count;
	ssize_t len;
	int par_addr_cells, par_size_cells;
	int tuple_size, tuples, rv, pins, i, j;
	int mpp_pin, mpp_function;

	/*
	 * Try to access the MPP node directly i.e. through /aliases/mpp.
	 */
	if ((node = OF_finddevice("mpp")) != -1)
		if (ofw_bus_node_is_compatible(node, "mrvl,mpp"))
			goto moveon;
	/*
	 * Find the node the long way.
	 */
	if ((node = OF_finddevice("/")) == -1)
		return (ENXIO);

	if ((node = fdt_find_compatible(node, "simple-bus", 0)) == 0)
		return (ENXIO);

	if ((node = fdt_find_compatible(node, "mrvl,mpp", 0)) == 0)
		/*
		 * No MPP node. Fall back to how MPP got set by the
		 * first-stage loader and try to continue booting.
		 */
		return (0);
moveon:
	/*
	 * Process 'reg' prop.
	 */
	if ((rv = fdt_addrsize_cells(OF_parent(node), &par_addr_cells,
	    &par_size_cells)) != 0)
		return(ENXIO);

	tuple_size = sizeof(pcell_t) * (par_addr_cells + par_size_cells);
	len = OF_getprop(node, "reg", reg, sizeof(reg));
	tuples = len / tuple_size;
	if (tuple_size <= 0)
		return (EINVAL);

	/*
	 * Get address/size. XXX we assume only the first 'reg' tuple is used.
	 */
	rv = fdt_data_to_res(reg, par_addr_cells, par_size_cells,
	    &start, &size);
	if (rv != 0)
		return (rv);
	start += fdt_immr_va;

	/*
	 * Process 'pin-count' and 'pin-map' props.
	 */
	if (OF_getencprop(node, "pin-count", &pin_count, sizeof(pin_count)) <= 0)
		return (ENXIO);
	if (pin_count > MPP_PIN_MAX)
		return (ERANGE);

	if (OF_getencprop(node, "#pin-cells", &pin_cells, sizeof(pin_cells)) <= 0)
		pin_cells = MPP_PIN_CELLS;
	if (pin_cells > MPP_PIN_CELLS)
		return (ERANGE);
	tuple_size = sizeof(pcell_t) * pin_cells;

	bzero(pinmap, sizeof(pinmap));
	len = OF_getencprop(node, "pin-map", pinmap, sizeof(pinmap));
	if (len <= 0)
		return (ERANGE);
	if (len % tuple_size)
		return (ERANGE);
	pins = len / tuple_size;
	if (pins > pin_count)
		return (ERANGE);
	/*
	 * Fill out a "mpp[pin] => function" table. All pins unspecified in
	 * the 'pin-map' property are defaulted to 0 function i.e. GPIO.
	 */
	bzero(mpp, sizeof(mpp));
	pinmap_ptr = pinmap;
	for (i = 0; i < pins; i++) {
		mpp_pin = *pinmap_ptr;
		mpp_function = *(pinmap_ptr + 1);
		mpp[mpp_pin] = mpp_function;
		pinmap_ptr += pin_cells;
	}

	/*
	 * Prepare and program MPP control register values.
	 */
	ctrl_offset = 0;
	for (i = 0; i < pin_count;) {
		ctrl_val = 0;

		for (j = 0; j < MPP_PINS_PER_REG; j++) {
			if (i + j == pin_count - 1)
				break;
			ctrl_val |= MPP_SEL(i + j, mpp[i + j]);
		}
		i += MPP_PINS_PER_REG;
		bus_space_write_4(fdtbus_bs_tag, start, ctrl_offset,
		    ctrl_val);

#if defined(SOC_MV_ORION)
		/*
		 * Third MPP reg on Orion SoC is placed
		 * non-linearly (with different offset).
		 */
		if (i ==  (2 * MPP_PINS_PER_REG))
			ctrl_offset = 0x50;
		else
#endif
			ctrl_offset += 4;
	}

	return (0);
}