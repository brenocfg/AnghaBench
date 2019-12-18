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
struct zpci_dev {int /*<<< orphan*/  max_bus_speed; int /*<<< orphan*/  fmb_update; int /*<<< orphan*/  max_msi; int /*<<< orphan*/  msi_addr; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  tlb_refresh; } ;
struct clp_rsp_query_pci_grp {int version; int /*<<< orphan*/  mui; int /*<<< orphan*/  noi; int /*<<< orphan*/  msia; int /*<<< orphan*/  dasm; int /*<<< orphan*/  refresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_SPEED_5_0GT ; 
 int /*<<< orphan*/  PCI_SPEED_UNKNOWN ; 

__attribute__((used)) static void clp_store_query_pci_fngrp(struct zpci_dev *zdev,
				      struct clp_rsp_query_pci_grp *response)
{
	zdev->tlb_refresh = response->refresh;
	zdev->dma_mask = response->dasm;
	zdev->msi_addr = response->msia;
	zdev->max_msi = response->noi;
	zdev->fmb_update = response->mui;

	switch (response->version) {
	case 1:
		zdev->max_bus_speed = PCIE_SPEED_5_0GT;
		break;
	default:
		zdev->max_bus_speed = PCI_SPEED_UNKNOWN;
		break;
	}
}