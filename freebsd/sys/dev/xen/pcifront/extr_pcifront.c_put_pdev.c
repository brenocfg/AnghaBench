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
struct pcifront_device {scalar_t__ ref_cnt; scalar_t__ evtchn; scalar_t__ gnt_ref; TYPE_1__* xdev; scalar_t__ sh_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct pcifront_device*,scalar_t__) ; 
 scalar_t__ INVALID_EVTCHN ; 
 scalar_t__ INVALID_GRANT_REF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct pcifront_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
put_pdev(struct pcifront_device *pdev)
{
	if (--pdev->ref_cnt > 0)
		return;

	DPRINTF("freeing pdev @ 0x%p (ref_cnt=%d)\n", pdev, pdev->ref_cnt);

	if (pdev->evtchn != INVALID_EVTCHN)
		xenbus_free_evtchn(pdev->xdev, pdev->evtchn);

	if (pdev->gnt_ref != INVALID_GRANT_REF)
		gnttab_end_foreign_access(pdev->gnt_ref, 0, (void *)pdev->sh_info);

	pdev->xdev->data = NULL;

	free(pdev, M_DEVBUF);
}