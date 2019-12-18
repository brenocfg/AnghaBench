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
struct al_pcie_port {int rev_id; } ;

/* Variables and functions */

int al_pcie_port_rev_id_get(struct al_pcie_port *pcie_port)
{
	return pcie_port->rev_id;
}