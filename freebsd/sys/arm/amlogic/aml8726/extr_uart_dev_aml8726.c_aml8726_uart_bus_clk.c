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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;

/* Variables and functions */
 int OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  OF_node_from_xref (scalar_t__) ; 

__attribute__((used)) static unsigned int
aml8726_uart_bus_clk(phandle_t node)
{
	pcell_t prop;
	ssize_t len;
	phandle_t clk_node;

	len = OF_getencprop(node, "clocks", &prop, sizeof(prop));
	if ((len / sizeof(prop)) != 1 || prop == 0 ||
	    (clk_node = OF_node_from_xref(prop)) == 0)
		return (0);

	len = OF_getencprop(clk_node, "clock-frequency", &prop, sizeof(prop));
	if ((len / sizeof(prop)) != 1 || prop == 0)
		return (0);

	return ((unsigned int)prop);
}