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
typedef  int /*<<< orphan*/  shift ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_uart_get_shift(device_t dev)
{
	phandle_t node;
	pcell_t shift;

	node = ofw_bus_get_node(dev);
	if ((OF_getencprop(node, "reg-shift", &shift, sizeof(shift))) <= 0)
		shift = 2;
	return ((int)shift);
}