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
struct pnv_phb {scalar_t__ model; int /*<<< orphan*/  opal_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_PCI_TCE_KILL ; 
 scalar_t__ PNV_PHB_MODEL_NPU ; 
 scalar_t__ PNV_PHB_MODEL_PHB3 ; 
 int /*<<< orphan*/  opal_pci_tce_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_pci_phb3_tce_invalidate_entire (struct pnv_phb*,int) ; 

void pnv_pci_ioda2_tce_invalidate_entire(struct pnv_phb *phb, bool rm)
{
	if (phb->model == PNV_PHB_MODEL_NPU || phb->model == PNV_PHB_MODEL_PHB3)
		pnv_pci_phb3_tce_invalidate_entire(phb, rm);
	else
		opal_pci_tce_kill(phb->opal_id, OPAL_PCI_TCE_KILL, 0, 0, 0, 0);
}