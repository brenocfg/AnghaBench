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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;

/* Variables and functions */
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 

int
uart_fdt_get_clock(phandle_t node, pcell_t *cell)
{

	/* clock-frequency is a FreeBSD-only extension. */
	if ((OF_getencprop(node, "clock-frequency", cell,
	    sizeof(*cell))) <= 0) {
		/* Try to retrieve parent 'bus-frequency' */
		/* XXX this should go to simple-bus fixup or so */
		if ((OF_getencprop(OF_parent(node), "bus-frequency", cell,
		    sizeof(*cell))) <= 0)
			*cell = 0;
	}

	return (0);
}