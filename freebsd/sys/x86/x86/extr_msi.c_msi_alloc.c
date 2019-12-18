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
typedef  void* u_int ;
struct TYPE_2__ {scalar_t__ is_handlers; } ;
struct msi_intsrc {int msi_cpu; int msi_vector; int msi_irq; int msi_count; int msi_maxcount; void** msi_irqs; TYPE_1__ msi_intsrc; struct msi_intsrc* msi_first; int /*<<< orphan*/ * msi_dev; void* msi_remap_cookie; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOSPC ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_MSI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int apic_alloc_vectors (void*,int*,int,int) ; 
 int /*<<< orphan*/  apic_free_vector (void*,int,int) ; 
 int /*<<< orphan*/  bcopy (int*,void**,int) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_get_domain (int /*<<< orphan*/ *,void**) ; 
 int first_msi_irq ; 
 int /*<<< orphan*/  free (void**,int /*<<< orphan*/ ) ; 
 scalar_t__ intr_lookup_source (int) ; 
 void* intr_next_cpu (void*) ; 
 int iommu_alloc_msi_intr (int /*<<< orphan*/ *,void**,int) ; 
 void** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_create_source () ; 
 int /*<<< orphan*/  msi_enabled ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int num_msi_irqs ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

int
msi_alloc(device_t dev, int count, int maxcount, int *irqs)
{
	struct msi_intsrc *msi, *fsrc;
	u_int cpu, domain, *mirqs;
	int cnt, i, vector;
#ifdef ACPI_DMAR
	u_int cookies[count];
	int error;
#endif

	if (!msi_enabled)
		return (ENXIO);

	if (bus_get_domain(dev, &domain) != 0)
		domain = 0;

	if (count > 1)
		mirqs = malloc(count * sizeof(*mirqs), M_MSI, M_WAITOK);
	else
		mirqs = NULL;
again:
	mtx_lock(&msi_lock);

	/* Try to find 'count' free IRQs. */
	cnt = 0;
	for (i = first_msi_irq; i < first_msi_irq + num_msi_irqs; i++) {
		msi = (struct msi_intsrc *)intr_lookup_source(i);

		/* End of allocated sources, so break. */
		if (msi == NULL)
			break;

		/* If this is a free one, save its IRQ in the array. */
		if (msi->msi_dev == NULL) {
			irqs[cnt] = i;
			cnt++;
			if (cnt == count)
				break;
		}
	}

	/* Do we need to create some new sources? */
	if (cnt < count) {
		/* If we would exceed the max, give up. */
		if (i + (count - cnt) > first_msi_irq + num_msi_irqs) {
			mtx_unlock(&msi_lock);
			free(mirqs, M_MSI);
			return (ENXIO);
		}
		mtx_unlock(&msi_lock);

		/* We need count - cnt more sources. */
		while (cnt < count) {
			msi_create_source();
			cnt++;
		}
		goto again;
	}

	/* Ok, we now have the IRQs allocated. */
	KASSERT(cnt == count, ("count mismatch"));

	/* Allocate 'count' IDT vectors. */
	cpu = intr_next_cpu(domain);
	vector = apic_alloc_vectors(cpu, irqs, count, maxcount);
	if (vector == 0) {
		mtx_unlock(&msi_lock);
		free(mirqs, M_MSI);
		return (ENOSPC);
	}

#ifdef ACPI_DMAR
	mtx_unlock(&msi_lock);
	error = iommu_alloc_msi_intr(dev, cookies, count);
	mtx_lock(&msi_lock);
	if (error == EOPNOTSUPP)
		error = 0;
	if (error != 0) {
		for (i = 0; i < count; i++)
			apic_free_vector(cpu, vector + i, irqs[i]);
		free(mirqs, M_MSI);
		return (error);
	}
	for (i = 0; i < count; i++) {
		msi = (struct msi_intsrc *)intr_lookup_source(irqs[i]);
		msi->msi_remap_cookie = cookies[i];
	}
#endif

	/* Assign IDT vectors and make these messages owned by 'dev'. */
	fsrc = (struct msi_intsrc *)intr_lookup_source(irqs[0]);
	for (i = 0; i < count; i++) {
		msi = (struct msi_intsrc *)intr_lookup_source(irqs[i]);
		msi->msi_cpu = cpu;
		msi->msi_dev = dev;
		msi->msi_vector = vector + i;
		if (bootverbose)
			printf(
		    "msi: routing MSI IRQ %d to local APIC %u vector %u\n",
			    msi->msi_irq, msi->msi_cpu, msi->msi_vector);
		msi->msi_first = fsrc;
		KASSERT(msi->msi_intsrc.is_handlers == 0,
		    ("dead MSI has handlers"));
	}
	fsrc->msi_count = count;
	fsrc->msi_maxcount = maxcount;
	if (count > 1)
		bcopy(irqs, mirqs, count * sizeof(*mirqs));
	fsrc->msi_irqs = mirqs;
	mtx_unlock(&msi_lock);
	return (0);
}