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
struct AdapterControlBlock {int msix_vectors; int* irq_id; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  acb_flags; int /*<<< orphan*/ * ih; int /*<<< orphan*/ ** irqres; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_MSIX_ENABLED ; 
 int FALSE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int TRUE ; 
 int /*<<< orphan*/  arcmsr_intr_handler ; 
 int /*<<< orphan*/  arcmsr_teardown_intr (int /*<<< orphan*/ ,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct AdapterControlBlock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int arcmsr_setup_msix(struct AdapterControlBlock *acb)
{
	int i;

	for (i = 0; i < acb->msix_vectors; i++) {
		acb->irq_id[i] = 1 + i;
		acb->irqres[i] = bus_alloc_resource_any(acb->pci_dev,
		    SYS_RES_IRQ, &acb->irq_id[i], RF_ACTIVE);
		if (acb->irqres[i] == NULL) {
			printf("arcmsr: Can't allocate MSI-X resource\n");
			goto irq_alloc_failed;
		}
		if (bus_setup_intr(acb->pci_dev, acb->irqres[i],
		    INTR_MPSAFE | INTR_TYPE_CAM, NULL, arcmsr_intr_handler,
		    acb, &acb->ih[i])) {
			printf("arcmsr: Cannot set up MSI-X interrupt handler\n");
			goto irq_alloc_failed;
		}
	}
	printf("arcmsr: MSI-X INT enabled\n");
	acb->acb_flags |= ACB_F_MSIX_ENABLED;
	return TRUE;

irq_alloc_failed:
	arcmsr_teardown_intr(acb->pci_dev, acb);
	return FALSE;
}