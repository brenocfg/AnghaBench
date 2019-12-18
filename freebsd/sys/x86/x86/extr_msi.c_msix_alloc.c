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
typedef  int u_int ;
struct TYPE_2__ {scalar_t__ is_handlers; } ;
struct msi_intsrc {int msi_remap_cookie; int msi_irq; int msi_cpu; int msi_vector; int msi_msix; int msi_count; int msi_maxcount; TYPE_1__ msi_intsrc; int /*<<< orphan*/ * msi_irqs; struct msi_intsrc* msi_first; int /*<<< orphan*/ * msi_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOSPC ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int apic_alloc_vector (int,int) ; 
 int /*<<< orphan*/  apic_free_vector (int,int,int) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_get_domain (int /*<<< orphan*/ *,int*) ; 
 int first_msi_irq ; 
 scalar_t__ intr_lookup_source (int) ; 
 int intr_next_cpu (int) ; 
 int iommu_alloc_msi_intr (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  msi_create_source () ; 
 int /*<<< orphan*/  msi_enabled ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int num_msi_irqs ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

int
msix_alloc(device_t dev, int *irq)
{
	struct msi_intsrc *msi;
	u_int cpu, domain;
	int i, vector;
#ifdef ACPI_DMAR
	u_int cookie;
	int error;
#endif

	if (!msi_enabled)
		return (ENXIO);

	if (bus_get_domain(dev, &domain) != 0)
		domain = 0;

again:
	mtx_lock(&msi_lock);

	/* Find a free IRQ. */
	for (i = first_msi_irq; i < first_msi_irq + num_msi_irqs; i++) {
		msi = (struct msi_intsrc *)intr_lookup_source(i);

		/* End of allocated sources, so break. */
		if (msi == NULL)
			break;

		/* Stop at the first free source. */
		if (msi->msi_dev == NULL)
			break;
	}

	/* Are all IRQs in use? */
	if (i == first_msi_irq + num_msi_irqs) {
		mtx_unlock(&msi_lock);
		return (ENXIO);
	}

	/* Do we need to create a new source? */
	if (msi == NULL) {
		mtx_unlock(&msi_lock);

		/* Create a new source. */
		msi_create_source();
		goto again;
	}

	/* Allocate an IDT vector. */
	cpu = intr_next_cpu(domain);
	vector = apic_alloc_vector(cpu, i);
	if (vector == 0) {
		mtx_unlock(&msi_lock);
		return (ENOSPC);
	}

	msi->msi_dev = dev;
#ifdef ACPI_DMAR
	mtx_unlock(&msi_lock);
	error = iommu_alloc_msi_intr(dev, &cookie, 1);
	mtx_lock(&msi_lock);
	if (error == EOPNOTSUPP)
		error = 0;
	if (error != 0) {
		msi->msi_dev = NULL;
		apic_free_vector(cpu, vector, i);
		return (error);
	}
	msi->msi_remap_cookie = cookie;
#endif

	if (bootverbose)
		printf("msi: routing MSI-X IRQ %d to local APIC %u vector %u\n",
		    msi->msi_irq, cpu, vector);

	/* Setup source. */
	msi->msi_cpu = cpu;
	msi->msi_first = msi;
	msi->msi_vector = vector;
	msi->msi_msix = 1;
	msi->msi_count = 1;
	msi->msi_maxcount = 1;
	msi->msi_irqs = NULL;

	KASSERT(msi->msi_intsrc.is_handlers == 0, ("dead MSI-X has handlers"));
	mtx_unlock(&msi_lock);

	*irq = i;
	return (0);
}