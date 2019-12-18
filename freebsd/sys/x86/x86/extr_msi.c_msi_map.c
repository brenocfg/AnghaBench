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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct msi_intsrc {int msi_count; int msi_irq; int /*<<< orphan*/  msi_remap_cookie; int /*<<< orphan*/  msi_vector; int /*<<< orphan*/  msi_cpu; int /*<<< orphan*/ * msi_dev; struct msi_intsrc* msi_first; int /*<<< orphan*/  msi_msix; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INTEL_ADDR (struct msi_intsrc*) ; 
 int /*<<< orphan*/  INTEL_DATA (struct msi_intsrc*) ; 
 int first_msi_irq ; 
 scalar_t__ intr_lookup_source (int) ; 
 int iommu_map_msi_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int num_msi_irqs ; 

int
msi_map(int irq, uint64_t *addr, uint32_t *data)
{
	struct msi_intsrc *msi;
	int error;
#ifdef ACPI_DMAR
	struct msi_intsrc *msi1;
	int i, k;
#endif

	mtx_lock(&msi_lock);
	msi = (struct msi_intsrc *)intr_lookup_source(irq);
	if (msi == NULL) {
		mtx_unlock(&msi_lock);
		return (ENOENT);
	}

	/* Make sure this message is allocated to a device. */
	if (msi->msi_dev == NULL) {
		mtx_unlock(&msi_lock);
		return (ENXIO);
	}

	/*
	 * If this message isn't an MSI-X message, make sure it's part
	 * of a group, and switch to the first message in the
	 * group.
	 */
	if (!msi->msi_msix) {
		if (msi->msi_first == NULL) {
			mtx_unlock(&msi_lock);
			return (ENXIO);
		}
		msi = msi->msi_first;
	}

#ifdef ACPI_DMAR
	if (!msi->msi_msix) {
		for (k = msi->msi_count - 1, i = first_msi_irq; k > 0 &&
		    i < first_msi_irq + num_msi_irqs; i++) {
			if (i == msi->msi_irq)
				continue;
			msi1 = (struct msi_intsrc *)intr_lookup_source(i);
			if (!msi1->msi_msix && msi1->msi_first == msi) {
				mtx_unlock(&msi_lock);
				iommu_map_msi_intr(msi1->msi_dev,
				    msi1->msi_cpu, msi1->msi_vector,
				    msi1->msi_remap_cookie, NULL, NULL);
				k--;
				mtx_lock(&msi_lock);
			}
		}
	}
	mtx_unlock(&msi_lock);
	error = iommu_map_msi_intr(msi->msi_dev, msi->msi_cpu,
	    msi->msi_vector, msi->msi_remap_cookie, addr, data);
#else
	mtx_unlock(&msi_lock);
	error = EOPNOTSUPP;
#endif
	if (error == EOPNOTSUPP) {
		*addr = INTEL_ADDR(msi);
		*data = INTEL_DATA(msi);
		error = 0;
	}
	return (error);
}