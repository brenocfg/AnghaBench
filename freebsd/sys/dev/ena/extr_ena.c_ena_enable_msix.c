#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {int dummy; } ;
struct ena_adapter {int num_queues; int msix_vecs; TYPE_1__* msix_entries; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int entry; int vector; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENA_ADMIN_MSIX_VEC ; 
 int /*<<< orphan*/  ENA_DBG ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int ENA_MAX_MSIX_VEC (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_enable_msix(struct ena_adapter *adapter)
{
	device_t dev = adapter->pdev;
	int msix_vecs, msix_req;
	int i, rc = 0;

	if (ENA_FLAG_ISSET(ENA_FLAG_MSIX_ENABLED, adapter)) {
		device_printf(dev, "Error, MSI-X is already enabled\n");
		return (EINVAL);
	}

	/* Reserved the max msix vectors we might need */
	msix_vecs = ENA_MAX_MSIX_VEC(adapter->num_queues);

	adapter->msix_entries = malloc(msix_vecs * sizeof(struct msix_entry),
	    M_DEVBUF, M_WAITOK | M_ZERO);

	ena_trace(ENA_DBG, "trying to enable MSI-X, vectors: %d\n", msix_vecs);

	for (i = 0; i < msix_vecs; i++) {
		adapter->msix_entries[i].entry = i;
		/* Vectors must start from 1 */
		adapter->msix_entries[i].vector = i + 1;
	}

	msix_req = msix_vecs;
	rc = pci_alloc_msix(dev, &msix_vecs);
	if (unlikely(rc != 0)) {
		device_printf(dev,
		    "Failed to enable MSIX, vectors %d rc %d\n", msix_vecs, rc);

		rc = ENOSPC;
		goto err_msix_free;
	}

	if (msix_vecs != msix_req) {
		if (msix_vecs == ENA_ADMIN_MSIX_VEC) {
			device_printf(dev,
			    "Not enough number of MSI-x allocated: %d\n",
			    msix_vecs);
			pci_release_msi(dev);
			rc = ENOSPC;
			goto err_msix_free;
		}
		device_printf(dev, "Enable only %d MSI-x (out of %d), reduce "
		    "the number of queues\n", msix_vecs, msix_req);
		adapter->num_queues = msix_vecs - ENA_ADMIN_MSIX_VEC;
	}

	adapter->msix_vecs = msix_vecs;
	ENA_FLAG_SET_ATOMIC(ENA_FLAG_MSIX_ENABLED, adapter);

	return (0);

err_msix_free:
	free(adapter->msix_entries, M_DEVBUF);
	adapter->msix_entries = NULL;

	return (rc);
}