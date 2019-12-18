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
struct TYPE_7__ {int /*<<< orphan*/  vdisk_size; int /*<<< orphan*/  vdisk_sectorsz; } ;
typedef  TYPE_3__ vdisk_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_5__ {TYPE_2__* d_dev; } ;
struct disk_devdesc {TYPE_1__ dd; } ;
struct devdesc {int dummy; } ;
struct TYPE_6__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int EINVAL ; 
 int ENOTTY ; 
 int disk_ioctl (struct disk_devdesc*,int /*<<< orphan*/ ,void*) ; 
 TYPE_3__* vdisk_get_info (struct devdesc*) ; 

__attribute__((used)) static int
vdisk_ioctl(struct open_file *f, u_long cmd, void *data)
{
	struct disk_devdesc *dev;
	vdisk_info_t *vd;
	int rc;

	dev = (struct disk_devdesc *)(f->f_devdata);
	if (dev == NULL)
		return (EINVAL);
	vd = vdisk_get_info((struct devdesc *)dev);
	if (vd == NULL)
		return (EINVAL);

	if (dev->dd.d_dev->dv_type == DEVT_DISK) {
		rc = disk_ioctl(dev, cmd, data);
		if (rc != ENOTTY)
			return (rc);
	}

	switch (cmd) {
	case DIOCGSECTORSIZE:
		*(u_int *)data = vd->vdisk_sectorsz;
		break;
	case DIOCGMEDIASIZE:
		*(uint64_t *)data = vd->vdisk_size;
		break;
	default:
		return (ENOTTY);
	}
	return (0);
}