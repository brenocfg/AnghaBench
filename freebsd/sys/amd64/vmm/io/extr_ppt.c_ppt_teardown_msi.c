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
struct resource {int dummy; } ;
struct TYPE_2__ {int num_msgs; int startrid; int /*<<< orphan*/ ** cookie; struct resource** res; } ;
struct pptdev {TYPE_1__ msi; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ppt_teardown_msi(struct pptdev *ppt)
{
	int i, rid;
	void *cookie;
	struct resource *res;

	if (ppt->msi.num_msgs == 0)
		return;

	for (i = 0; i < ppt->msi.num_msgs; i++) {
		rid = ppt->msi.startrid + i;
		res = ppt->msi.res[i];
		cookie = ppt->msi.cookie[i];

		if (cookie != NULL)
			bus_teardown_intr(ppt->dev, res, cookie);

		if (res != NULL)
			bus_release_resource(ppt->dev, SYS_RES_IRQ, rid, res);
		
		ppt->msi.res[i] = NULL;
		ppt->msi.cookie[i] = NULL;
	}

	if (ppt->msi.startrid == 1)
		pci_release_msi(ppt->dev);

	ppt->msi.num_msgs = 0;
}