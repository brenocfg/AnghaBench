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
struct TYPE_7__ {int /*<<< orphan*/  vdisk_open; } ;
typedef  TYPE_3__ vdisk_info_t ;
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_6__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {TYPE_2__ dd; } ;
struct devdesc {int dummy; } ;
struct TYPE_5__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 int EINVAL ; 
 int disk_close (struct disk_devdesc*) ; 
 TYPE_3__* vdisk_get_info (struct devdesc*) ; 

__attribute__((used)) static int
vdisk_close(struct open_file *f)
{
	struct disk_devdesc *dev;
	vdisk_info_t *vd;

	dev = (struct disk_devdesc *)(f->f_devdata);
	if (dev == NULL)
		return (EINVAL);
	vd = vdisk_get_info((struct devdesc *)dev);
	if (vd == NULL)
		return (EINVAL);

	vd->vdisk_open--;
	if (dev->dd.d_dev->dv_type == DEVT_DISK)
		return (disk_close(dev));
	return (0);
}