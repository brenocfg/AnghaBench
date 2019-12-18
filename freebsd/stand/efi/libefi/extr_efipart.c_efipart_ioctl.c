#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_8__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {TYPE_2__ dd; } ;
struct devdesc {int dummy; } ;
struct TYPE_11__ {TYPE_4__* pd_blkio; } ;
typedef  TYPE_5__ pdinfo_t ;
struct TYPE_10__ {TYPE_3__* Media; } ;
struct TYPE_9__ {int BlockSize; int /*<<< orphan*/  LastBlock; } ;
struct TYPE_7__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int EINVAL ; 
 int ENOTTY ; 
 int disk_ioctl (struct disk_devdesc*,int /*<<< orphan*/ ,void*) ; 
 TYPE_5__* efiblk_get_pdinfo (struct devdesc*) ; 

__attribute__((used)) static int
efipart_ioctl(struct open_file *f, u_long cmd, void *data)
{
	struct disk_devdesc *dev;
	pdinfo_t *pd;
	int rc;

	dev = (struct disk_devdesc *)(f->f_devdata);
	if (dev == NULL)
		return (EINVAL);

	pd = efiblk_get_pdinfo((struct devdesc *)dev);
	if (pd == NULL)
		return (EINVAL);

	if (dev->dd.d_dev->dv_type == DEVT_DISK) {
		rc = disk_ioctl(dev, cmd, data);
		if (rc != ENOTTY)
			return (rc);
	}

	switch (cmd) {
	case DIOCGSECTORSIZE:
		*(u_int *)data = pd->pd_blkio->Media->BlockSize;
		break;
	case DIOCGMEDIASIZE:
		*(uint64_t *)data = pd->pd_blkio->Media->BlockSize *
		    (pd->pd_blkio->Media->LastBlock + 1);
		break;
	default:
		return (ENOTTY);
	}

	return (0);
}