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
struct msi_intsrc {int msi_count; int /*<<< orphan*/ * msi_irqs; scalar_t__ msi_maxcount; scalar_t__ msi_vector; int /*<<< orphan*/  msi_irq; int /*<<< orphan*/  msi_cpu; int /*<<< orphan*/ * msi_dev; struct msi_intsrc* msi_first; int /*<<< orphan*/  msi_remap_cookie; scalar_t__ msi_msix; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_MSI ; 
 int /*<<< orphan*/  apic_free_vector (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ intr_lookup_source (int) ; 
 int /*<<< orphan*/  iommu_unmap_msi_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
msi_release(int *irqs, int count)
{
	struct msi_intsrc *msi, *first;
	int i;

	mtx_lock(&msi_lock);
	first = (struct msi_intsrc *)intr_lookup_source(irqs[0]);
	if (first == NULL) {
		mtx_unlock(&msi_lock);
		return (ENOENT);
	}

	/* Make sure this isn't an MSI-X message. */
	if (first->msi_msix) {
		mtx_unlock(&msi_lock);
		return (EINVAL);
	}

	/* Make sure this message is allocated to a group. */
	if (first->msi_first == NULL) {
		mtx_unlock(&msi_lock);
		return (ENXIO);
	}

	/*
	 * Make sure this is the start of a group and that we are releasing
	 * the entire group.
	 */
	if (first->msi_first != first || first->msi_count != count) {
		mtx_unlock(&msi_lock);
		return (EINVAL);
	}
	KASSERT(first->msi_dev != NULL, ("unowned group"));

	/* Clear all the extra messages in the group. */
	for (i = 1; i < count; i++) {
		msi = (struct msi_intsrc *)intr_lookup_source(irqs[i]);
		KASSERT(msi->msi_first == first, ("message not in group"));
		KASSERT(msi->msi_dev == first->msi_dev, ("owner mismatch"));
#ifdef ACPI_DMAR
		iommu_unmap_msi_intr(first->msi_dev, msi->msi_remap_cookie);
#endif
		msi->msi_first = NULL;
		msi->msi_dev = NULL;
		apic_free_vector(msi->msi_cpu, msi->msi_vector, msi->msi_irq);
		msi->msi_vector = 0;
	}

	/* Clear out the first message. */
#ifdef ACPI_DMAR
	mtx_unlock(&msi_lock);
	iommu_unmap_msi_intr(first->msi_dev, first->msi_remap_cookie);
	mtx_lock(&msi_lock);
#endif
	first->msi_first = NULL;
	first->msi_dev = NULL;
	apic_free_vector(first->msi_cpu, first->msi_vector, first->msi_irq);
	first->msi_vector = 0;
	first->msi_count = 0;
	first->msi_maxcount = 0;
	free(first->msi_irqs, M_MSI);
	first->msi_irqs = NULL;

	mtx_unlock(&msi_lock);
	return (0);
}