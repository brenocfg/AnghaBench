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
struct msi_intsrc {scalar_t__ msi_maxcount; scalar_t__ msi_count; scalar_t__ msi_msix; scalar_t__ msi_vector; int /*<<< orphan*/  msi_irq; int /*<<< orphan*/  msi_cpu; int /*<<< orphan*/ * msi_dev; int /*<<< orphan*/ * msi_first; int /*<<< orphan*/  msi_remap_cookie; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  apic_free_vector (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ intr_lookup_source (int) ; 
 int /*<<< orphan*/  iommu_unmap_msi_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
msix_release(int irq)
{
	struct msi_intsrc *msi;

	mtx_lock(&msi_lock);
	msi = (struct msi_intsrc *)intr_lookup_source(irq);
	if (msi == NULL) {
		mtx_unlock(&msi_lock);
		return (ENOENT);
	}

	/* Make sure this is an MSI-X message. */
	if (!msi->msi_msix) {
		mtx_unlock(&msi_lock);
		return (EINVAL);
	}

	KASSERT(msi->msi_dev != NULL, ("unowned message"));

	/* Clear out the message. */
#ifdef ACPI_DMAR
	mtx_unlock(&msi_lock);
	iommu_unmap_msi_intr(msi->msi_dev, msi->msi_remap_cookie);
	mtx_lock(&msi_lock);
#endif
	msi->msi_first = NULL;
	msi->msi_dev = NULL;
	apic_free_vector(msi->msi_cpu, msi->msi_vector, msi->msi_irq);
	msi->msi_vector = 0;
	msi->msi_msix = 0;
	msi->msi_count = 0;
	msi->msi_maxcount = 0;

	mtx_unlock(&msi_lock);
	return (0);
}