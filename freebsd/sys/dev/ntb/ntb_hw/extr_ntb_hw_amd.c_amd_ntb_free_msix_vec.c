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
struct amd_ntb_softc {int /*<<< orphan*/ * msix_vec; scalar_t__ msix_vec_count; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AMD_NTB ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amd_ntb_free_msix_vec(struct amd_ntb_softc *ntb)
{
	if (ntb->msix_vec_count) {
		pci_release_msi(ntb->device);
		ntb->msix_vec_count = 0;
	}

	if (ntb->msix_vec != NULL) {
		free(ntb->msix_vec, M_AMD_NTB);
		ntb->msix_vec = NULL;
	}
}