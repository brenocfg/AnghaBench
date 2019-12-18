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
struct TYPE_2__ {int num_msgs; scalar_t__ msix_pba_rid; int /*<<< orphan*/ * msix_pba_res; scalar_t__ msix_table_rid; int /*<<< orphan*/ * msix_table_res; int /*<<< orphan*/  arg; int /*<<< orphan*/  cookie; int /*<<< orphan*/  res; } ;
struct pptdev {TYPE_1__ msix; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PPTMSIX ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppt_teardown_msix_intr (struct pptdev*,int) ; 

__attribute__((used)) static void 
ppt_teardown_msix(struct pptdev *ppt)
{
	int i;

	if (ppt->msix.num_msgs == 0) 
		return;

	for (i = 0; i < ppt->msix.num_msgs; i++) 
		ppt_teardown_msix_intr(ppt, i);

	free(ppt->msix.res, M_PPTMSIX);
	free(ppt->msix.cookie, M_PPTMSIX);
	free(ppt->msix.arg, M_PPTMSIX);

	pci_release_msi(ppt->dev);

	if (ppt->msix.msix_table_res) {
		bus_release_resource(ppt->dev, SYS_RES_MEMORY, 
				     ppt->msix.msix_table_rid,
				     ppt->msix.msix_table_res);
		ppt->msix.msix_table_res = NULL;
		ppt->msix.msix_table_rid = 0;
	}
	if (ppt->msix.msix_pba_res) {
		bus_release_resource(ppt->dev, SYS_RES_MEMORY, 
				     ppt->msix.msix_pba_rid,
				     ppt->msix.msix_pba_res);
		ppt->msix.msix_pba_res = NULL;
		ppt->msix.msix_pba_rid = 0;
	}

	ppt->msix.num_msgs = 0;
}