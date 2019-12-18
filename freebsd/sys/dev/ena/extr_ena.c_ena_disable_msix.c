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
struct ena_adapter {int /*<<< orphan*/ * msix_entries; scalar_t__ msix_vecs; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_CLEAR_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_disable_msix(struct ena_adapter *adapter)
{

	if (ENA_FLAG_ISSET(ENA_FLAG_MSIX_ENABLED, adapter)) {
		ENA_FLAG_CLEAR_ATOMIC(ENA_FLAG_MSIX_ENABLED, adapter);
		pci_release_msi(adapter->pdev);
	}

	adapter->msix_vecs = 0;
	if (adapter->msix_entries != NULL)
		free(adapter->msix_entries, M_DEVBUF);
	adapter->msix_entries = NULL;
}