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
typedef  int /*<<< orphan*/  phy_reg ;
typedef  int /*<<< orphan*/  phy_handle ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  OF_node_from_xref (int) ; 

__attribute__((used)) static int
xae_get_phyaddr(phandle_t node, int *phy_addr)
{
	phandle_t phy_node;
	pcell_t phy_handle, phy_reg;

	if (OF_getencprop(node, "phy-handle", (void *)&phy_handle,
	    sizeof(phy_handle)) <= 0)
		return (ENXIO);

	phy_node = OF_node_from_xref(phy_handle);

	if (OF_getencprop(phy_node, "reg", (void *)&phy_reg,
	    sizeof(phy_reg)) <= 0)
		return (ENXIO);

	*phy_addr = phy_reg;

	return (0);
}