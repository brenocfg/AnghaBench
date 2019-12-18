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
struct al_pcie_pf {int /*<<< orphan*/  pf_num; int /*<<< orphan*/  pcie_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_assert (struct al_pcie_pf*) ; 
 unsigned int al_pcie_aer_uncorr_get_and_clear_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int al_pcie_aer_uncorr_get_and_clear(struct al_pcie_pf *pcie_pf)
{
	al_assert(pcie_pf);

	return al_pcie_aer_uncorr_get_and_clear_aux(
			pcie_pf->pcie_port, pcie_pf->pf_num);
}