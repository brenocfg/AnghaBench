#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_6__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {TYPE_2__ dd; } ;
struct devdesc {int dummy; } ;
struct TYPE_7__ {scalar_t__ pd_open; int /*<<< orphan*/ * pd_bcache; int /*<<< orphan*/ * pd_blkio; } ;
typedef  TYPE_3__ pdinfo_t ;
struct TYPE_5__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 int EINVAL ; 
 int /*<<< orphan*/  bcache_free (int /*<<< orphan*/ *) ; 
 int disk_close (struct disk_devdesc*) ; 
 TYPE_3__* efiblk_get_pdinfo (struct devdesc*) ; 

__attribute__((used)) static int
efipart_close(struct open_file *f)
{
	struct disk_devdesc *dev;
	pdinfo_t *pd;

	dev = (struct disk_devdesc *)(f->f_devdata);
	if (dev == NULL)
		return (EINVAL);

	pd = efiblk_get_pdinfo((struct devdesc *)dev);
	if (pd == NULL)
		return (EINVAL);

	pd->pd_open--;
	if (pd->pd_open == 0) {
		pd->pd_blkio = NULL;
		bcache_free(pd->pd_bcache);
		pd->pd_bcache = NULL;
	}
	if (dev->dd.d_dev->dv_type == DEVT_DISK)
		return (disk_close(dev));
	return (0);
}