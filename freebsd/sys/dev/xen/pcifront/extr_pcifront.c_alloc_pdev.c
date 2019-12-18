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
struct xenbus_device {struct pcifront_device* data; int /*<<< orphan*/  nodename; } ;
struct xen_pci_sharedinfo {scalar_t__ flags; } ;
struct pcifront_device {int unit; int ref_cnt; int /*<<< orphan*/  gnt_ref; int /*<<< orphan*/  evtchn; int /*<<< orphan*/  sh_info_lock; struct xen_pci_sharedinfo* sh_info; struct xenbus_device* xdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct pcifront_device*,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INVALID_EVTCHN ; 
 int /*<<< orphan*/  INVALID_GRANT_REF ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pcifront_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pcifront_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pdev_list ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 

__attribute__((used)) static struct pcifront_device *
alloc_pdev(struct xenbus_device *xdev)
{
	struct pcifront_device *pdev = NULL;
	int err, unit;

	err = sscanf(xdev->nodename, "device/pci/%d", &unit);
	if (err != 1) {
		if (err == 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err, "Error scanning pci device instance number");
		goto out;
	}

	pdev = (struct pcifront_device *)malloc(sizeof(struct pcifront_device), M_DEVBUF, M_NOWAIT);
	if (pdev == NULL) {
		err = -ENOMEM;
		xenbus_dev_fatal(xdev, err, "Error allocating pcifront_device struct");
		goto out;
	}
	pdev->unit = unit;
	pdev->xdev = xdev;
	pdev->ref_cnt = 1;

	pdev->sh_info = (struct xen_pci_sharedinfo *)malloc(PAGE_SIZE, M_DEVBUF, M_NOWAIT);
	if (pdev->sh_info == NULL) {
		free(pdev, M_DEVBUF);
		pdev = NULL;
		err = -ENOMEM;
		xenbus_dev_fatal(xdev, err, "Error allocating sh_info struct");
		goto out;
	}
	pdev->sh_info->flags = 0;

	xdev->data = pdev;

	mtx_init(&pdev->sh_info_lock, "info_lock", "pci shared dev info lock", MTX_DEF);

	pdev->evtchn = INVALID_EVTCHN;
	pdev->gnt_ref = INVALID_GRANT_REF;

	STAILQ_INSERT_TAIL(&pdev_list, pdev, next);

	DPRINTF("Allocated pdev @ 0x%p (unit=%d)\n", pdev, unit);

 out:
	return pdev;
}