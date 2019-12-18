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
struct nicpf {TYPE_1__* msix_entries; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/ * irq_res; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int NIC_PF_INTR_ID_MBOX0 ; 
 int NIC_PF_INTR_ID_MBOX1 ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nicpf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nic_enable_mbx_intr (struct nicpf*) ; 
 int nic_enable_msix (struct nicpf*) ; 
 int /*<<< orphan*/  nic_free_all_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  nic_mbx0_intr_handler ; 
 int /*<<< orphan*/  nic_mbx1_intr_handler ; 

__attribute__((used)) static int
nic_register_interrupts(struct nicpf *nic)
{
	int irq, rid;
	int ret;

	/* Enable MSI-X */
	ret = nic_enable_msix(nic);
	if (ret != 0)
		return (ret);

	/* Register mailbox interrupt handlers */
	irq = NIC_PF_INTR_ID_MBOX0;
	rid = irq + 1;
	nic->msix_entries[irq].irq_res = bus_alloc_resource_any(nic->dev,
	    SYS_RES_IRQ, &rid, (RF_SHAREABLE | RF_ACTIVE));
	if (nic->msix_entries[irq].irq_res == NULL) {
		ret = ENXIO;
		goto fail;
	}
	ret = bus_setup_intr(nic->dev, nic->msix_entries[irq].irq_res,
	    (INTR_MPSAFE | INTR_TYPE_MISC), NULL, nic_mbx0_intr_handler, nic,
	    &nic->msix_entries[irq].handle);
	if (ret != 0)
		goto fail;

	irq = NIC_PF_INTR_ID_MBOX1;
	rid = irq + 1;
	nic->msix_entries[irq].irq_res = bus_alloc_resource_any(nic->dev,
	    SYS_RES_IRQ, &rid, (RF_SHAREABLE | RF_ACTIVE));
	if (nic->msix_entries[irq].irq_res == NULL) {
		ret = ENXIO;
		goto fail;
	}
	ret = bus_setup_intr(nic->dev, nic->msix_entries[irq].irq_res,
	    (INTR_MPSAFE | INTR_TYPE_MISC), NULL, nic_mbx1_intr_handler, nic,
	    &nic->msix_entries[irq].handle);
	if (ret != 0)
		goto fail;

	/* Enable mailbox interrupt */
	nic_enable_mbx_intr(nic);
	return (0);

fail:
	nic_free_all_interrupts(nic);
	return (ret);
}