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
struct pci_dev {int dummy; } ;
struct intel_uncore_box {int /*<<< orphan*/  flags; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVBEP_PMON_BOX_CTL_INT ; 
 int /*<<< orphan*/  SKX_M2M_PCI_PMON_BOX_CTL ; 
 int /*<<< orphan*/  UNCORE_BOX_FLAG_CTL_OFFS8 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skx_m2m_uncore_pci_init_box(struct intel_uncore_box *box)
{
	struct pci_dev *pdev = box->pci_dev;

	__set_bit(UNCORE_BOX_FLAG_CTL_OFFS8, &box->flags);
	pci_write_config_dword(pdev, SKX_M2M_PCI_PMON_BOX_CTL, IVBEP_PMON_BOX_CTL_INT);
}