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
struct pci_pbm_info {int /*<<< orphan*/ * msi_irq_table; int /*<<< orphan*/ * msiq_irq_cookies; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msi_table_free(struct pci_pbm_info *pbm)
{
	kfree(pbm->msiq_irq_cookies);
	pbm->msiq_irq_cookies = NULL;

	kfree(pbm->msi_irq_table);
	pbm->msi_irq_table = NULL;
}