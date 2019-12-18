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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int GMAC_MII_CLK_25_35M_DIV16 ; 
 int GMAC_MII_CLK_35_60M_DIV26 ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
if_dwc_socfpga_mii_clk(device_t dev)
{
	phandle_t root;

	root = OF_finddevice("/");

	if (ofw_bus_node_is_compatible(root, "altr,socfpga-stratix10"))
		return (GMAC_MII_CLK_35_60M_DIV26);

	/* Default value. */
	return (GMAC_MII_CLK_25_35M_DIV16);
}