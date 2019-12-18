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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ is_handlers; } ;
struct msi_intsrc {scalar_t__ msi_msix; int msi_vector; scalar_t__ msi_cpu; int msi_count; int* msi_irqs; int msi_irq; TYPE_1__ msi_intsrc; int /*<<< orphan*/  msi_dev; int /*<<< orphan*/  msi_maxcount; struct msi_intsrc* msi_first; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_REMAP_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int apic_alloc_vector (scalar_t__,int) ; 
 int apic_alloc_vectors (scalar_t__,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_disable_vector (scalar_t__,int) ; 
 int /*<<< orphan*/  apic_enable_vector (scalar_t__,int) ; 
 int /*<<< orphan*/  apic_free_vector (scalar_t__,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ intr_lookup_source (int) ; 
 scalar_t__ msix_disable_migration ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
msi_assign_cpu(struct intsrc *isrc, u_int apic_id)
{
	struct msi_intsrc *sib, *msi = (struct msi_intsrc *)isrc;
	int old_vector;
	u_int old_id;
	int i, vector;

	/*
	 * Only allow CPUs to be assigned to the first message for an
	 * MSI group.
	 */
	if (msi->msi_first != msi)
		return (EINVAL);

#ifdef SMP
	if (msix_disable_migration && msi->msi_msix)
		return (EINVAL);
#endif

	/* Store information to free existing irq. */
	old_vector = msi->msi_vector;
	old_id = msi->msi_cpu;
	if (old_id == apic_id)
		return (0);

	/* Allocate IDT vectors on this cpu. */
	if (msi->msi_count > 1) {
		KASSERT(msi->msi_msix == 0, ("MSI-X message group"));
		vector = apic_alloc_vectors(apic_id, msi->msi_irqs,
		    msi->msi_count, msi->msi_maxcount);
	} else
		vector = apic_alloc_vector(apic_id, msi->msi_irq);
	if (vector == 0)
		return (ENOSPC);

	msi->msi_cpu = apic_id;
	msi->msi_vector = vector;
	if (msi->msi_intsrc.is_handlers > 0)
		apic_enable_vector(msi->msi_cpu, msi->msi_vector);
	if (bootverbose)
		printf("msi: Assigning %s IRQ %d to local APIC %u vector %u\n",
		    msi->msi_msix ? "MSI-X" : "MSI", msi->msi_irq,
		    msi->msi_cpu, msi->msi_vector);
	for (i = 1; i < msi->msi_count; i++) {
		sib = (struct msi_intsrc *)intr_lookup_source(msi->msi_irqs[i]);
		sib->msi_cpu = apic_id;
		sib->msi_vector = vector + i;
		if (sib->msi_intsrc.is_handlers > 0)
			apic_enable_vector(sib->msi_cpu, sib->msi_vector);
		if (bootverbose)
			printf(
		    "msi: Assigning MSI IRQ %d to local APIC %u vector %u\n",
			    sib->msi_irq, sib->msi_cpu, sib->msi_vector);
	}
	BUS_REMAP_INTR(device_get_parent(msi->msi_dev), msi->msi_dev,
	    msi->msi_irq);

	/*
	 * Free the old vector after the new one is established.  This is done
	 * to prevent races where we could miss an interrupt.
	 */
	if (msi->msi_intsrc.is_handlers > 0)
		apic_disable_vector(old_id, old_vector);
	apic_free_vector(old_id, old_vector, msi->msi_irq);
	for (i = 1; i < msi->msi_count; i++) {
		sib = (struct msi_intsrc *)intr_lookup_source(msi->msi_irqs[i]);
		if (sib->msi_intsrc.is_handlers > 0)
			apic_disable_vector(old_id, old_vector + i);
		apic_free_vector(old_id, old_vector + i, msi->msi_irqs[i]);
	}
	return (0);
}