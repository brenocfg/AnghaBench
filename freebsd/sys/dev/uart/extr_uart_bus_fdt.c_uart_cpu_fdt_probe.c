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
typedef  void* u_int ;
struct uart_class {int dummy; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  br ;

/* Variables and functions */
 int ENXIO ; 
 int OF_decode_addr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getencprop (int,char*,void**,int) ; 
 char* kern_getenv (char*) ; 
 scalar_t__ phandle_chosen_propdev (int,char const*,int*) ; 
 scalar_t__ uart_fdt_find_by_node (int,int) ; 
 int uart_fdt_get_clock (int,void**) ; 
 scalar_t__ uart_fdt_get_io_width (int,void**) ; 
 scalar_t__ uart_fdt_get_shift (int,void**) ; 
 void* uart_getregiowidth (struct uart_class*) ; 
 void* uart_getregshift (struct uart_class*) ; 

int
uart_cpu_fdt_probe(struct uart_class **classp, bus_space_tag_t *bst,
    bus_space_handle_t *bsh, int *baud, u_int *rclk, u_int *shiftp,
    u_int *iowidthp)
{
	const char *propnames[] = {"stdout-path", "linux,stdout-path", "stdout",
	    "stdin-path", "stdin", NULL};
	const char **name;
	struct uart_class *class;
	phandle_t node, chosen;
	pcell_t br, clk, shift, iowidth;
	char *cp;
	int err;

	/* Has the user forced a specific device node? */
	cp = kern_getenv("hw.fdt.console");
	if (cp == NULL) {
		/*
		 * Retrieve /chosen/std{in,out}.
		 */
		node = -1;
		if ((chosen = OF_finddevice("/chosen")) != -1) {
			for (name = propnames; *name != NULL; name++) {
				if (phandle_chosen_propdev(chosen, *name,
				    &node) == 0)
					break;
			}
		}
		if (chosen == -1 || *name == NULL)
			node = OF_finddevice("serial0"); /* Last ditch */
	} else {
		node = OF_finddevice(cp);
	}

	if (node == -1)
		return (ENXIO);

	/*
	 * Check old style of UART definition first. Unfortunately, the common
	 * FDT processing is not possible if we have clock, power domains and
	 * pinmux stuff.
	 */
	class = (struct uart_class *)uart_fdt_find_by_node(node, 0);
	if (class != NULL) {
		if ((err = uart_fdt_get_clock(node, &clk)) != 0)
			return (err);
	} else {
		/* Check class only linker set */
		class =
		    (struct uart_class *)uart_fdt_find_by_node(node, 1);
		if (class == NULL)
			return (ENXIO);
		clk = 0;
	}

	/*
	 * Retrieve serial attributes.
	 */
	if (uart_fdt_get_shift(node, &shift) != 0)
		shift = uart_getregshift(class);

	if (uart_fdt_get_io_width(node, &iowidth) != 0)
		iowidth = uart_getregiowidth(class);

	if (OF_getencprop(node, "current-speed", &br, sizeof(br)) <= 0)
		br = 0;

	err = OF_decode_addr(node, 0, bst, bsh, NULL);
	if (err != 0)
		return (err);

	*classp = class;
	*baud = br;
	*rclk = clk;
	*shiftp = shift;
	*iowidthp = iowidth;

	return (0);
}