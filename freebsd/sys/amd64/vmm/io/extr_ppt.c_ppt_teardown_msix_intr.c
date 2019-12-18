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
struct TYPE_2__ {int startrid; int /*<<< orphan*/ ** cookie; struct resource** res; } ;
struct pptdev {TYPE_1__ msix; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,void*) ; 

__attribute__((used)) static void 
ppt_teardown_msix_intr(struct pptdev *ppt, int idx)
{
	int rid;
	struct resource *res;
	void *cookie;

	rid = ppt->msix.startrid + idx;
	res = ppt->msix.res[idx];
	cookie = ppt->msix.cookie[idx];

	if (cookie != NULL) 
		bus_teardown_intr(ppt->dev, res, cookie);

	if (res != NULL) 
		bus_release_resource(ppt->dev, SYS_RES_IRQ, rid, res);

	ppt->msix.res[idx] = NULL;
	ppt->msix.cookie[idx] = NULL;
}