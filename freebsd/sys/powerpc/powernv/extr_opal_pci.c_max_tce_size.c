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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  sizes ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  unsigned long long cell_t ;

/* Variables and functions */
 int OF_getencprop (int /*<<< orphan*/ ,char*,unsigned long long*,int) ; 
 unsigned long long OPAL_PCI_TCE_DEFAULT_SEG_SIZE ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
max_tce_size(device_t dev)
{
	phandle_t node;
	cell_t sizes[64]; /* Property is a list of bit-widths, up to 64-bits */
	int count;

	node = ofw_bus_get_node(dev);

	count = OF_getencprop(node, "ibm,supported-tce-sizes",
	    sizes, sizeof(sizes));
	if (count < (int) sizeof(cell_t))
		return OPAL_PCI_TCE_DEFAULT_SEG_SIZE;

	count /= sizeof(cell_t);

	return (1ULL << sizes[count - 1]);
}