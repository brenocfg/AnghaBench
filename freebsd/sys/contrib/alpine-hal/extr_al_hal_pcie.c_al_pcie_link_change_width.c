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
typedef  int /*<<< orphan*/  uint8_t ;
struct al_pcie_port {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 

int
al_pcie_link_change_width(struct al_pcie_port *pcie_port,
			      uint8_t width __attribute__((__unused__)))
{
	al_err("PCIe %d: link change width not implemented\n",
		pcie_port->port_id);

	return -ENOSYS;
}