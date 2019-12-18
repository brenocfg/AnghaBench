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
struct al_pcie_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_assert (struct al_pcie_port*) ; 
 unsigned int al_pcie_aer_corr_get_and_clear_aux (struct al_pcie_port*,int /*<<< orphan*/ ) ; 

unsigned int al_pcie_port_aer_corr_get_and_clear(
		struct al_pcie_port		*pcie_port)
{
	al_assert(pcie_port);

	/**
	* For RC mode there's no PFs (neither PF handles),
	* therefore PF#0 is used
	* */
	return al_pcie_aer_corr_get_and_clear_aux(pcie_port, 0);
}