#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcicfg_msix {scalar_t__ msix_alloc; int msix_msgnum; int msix_table_len; int /*<<< orphan*/  msix_ctrl; scalar_t__ msix_location; struct msix_vector* msix_vectors; struct msix_table_entry* msix_table; } ;
struct TYPE_2__ {struct pcicfg_msix msix; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
struct msix_vector {int /*<<< orphan*/  mv_data; int /*<<< orphan*/  mv_address; } ;
struct msix_table_entry {int mte_vector; scalar_t__ mte_handlers; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCIR_MSIX_CTRL ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_mask_msix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmask_msix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_msix_entry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_resume_msix(device_t dev)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	struct pcicfg_msix *msix = &dinfo->cfg.msix;
	struct msix_table_entry *mte;
	struct msix_vector *mv;
	int i;

	if (msix->msix_alloc > 0) {
		/* First, mask all vectors. */
		for (i = 0; i < msix->msix_msgnum; i++)
			pci_mask_msix(dev, i);

		/* Second, program any messages with at least one handler. */
		for (i = 0; i < msix->msix_table_len; i++) {
			mte = &msix->msix_table[i];
			if (mte->mte_vector == 0 || mte->mte_handlers == 0)
				continue;
			mv = &msix->msix_vectors[mte->mte_vector - 1];
			pci_write_msix_entry(dev, i, mv->mv_address,
			    mv->mv_data);
			pci_unmask_msix(dev, i);
		}
	}
	pci_write_config(dev, msix->msix_location + PCIR_MSIX_CTRL,
	    msix->msix_ctrl, 2);
}