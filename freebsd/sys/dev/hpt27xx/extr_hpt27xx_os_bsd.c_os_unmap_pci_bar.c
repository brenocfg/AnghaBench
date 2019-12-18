#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pcibar; int /*<<< orphan*/  pcidev; } ;
struct TYPE_3__ {void* base; int /*<<< orphan*/  res; int /*<<< orphan*/  rid; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__* PHBA ;

/* Variables and functions */
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void os_unmap_pci_bar(void *osext, void *base)
{
	PHBA hba = (PHBA)osext;
	int index;
	
	for (index=0; index<6; index++) {
		if (hba->pcibar[index].base==base) {
			bus_release_resource(hba->pcidev, hba->pcibar[index].type,
				hba->pcibar[index].rid, hba->pcibar[index].res);
			hba->pcibar[index].base = 0;
			return;
		}
	}
}