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
struct TYPE_7__ {int vdisk_sectorsz; int /*<<< orphan*/  vdisk_fd; } ;
typedef  TYPE_3__ vdisk_info_t ;
struct TYPE_6__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {int d_offset; TYPE_2__ dd; } ;
struct devdesc {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int daddr_t ;
struct TYPE_5__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 int EINVAL ; 
 int EIO ; 
 int ENOSYS ; 
 int F_MASK ; 
#define  F_READ 129 
#define  F_WRITE 128 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ errno ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t read (int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_3__* vdisk_get_info (struct devdesc*) ; 
 size_t write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
vdisk_strategy(void *devdata, int rw, daddr_t blk, size_t size,
    char *buf, size_t *rsize)
{
	struct disk_devdesc *dev;
	vdisk_info_t *vd;
	ssize_t rv;

	dev = devdata;
	if (dev == NULL)
		return (EINVAL);
	vd = vdisk_get_info((struct devdesc *)dev);
	if (vd == NULL)
		return (EINVAL);

	if (size == 0 || (size % 512) != 0)
		return (EIO);

	if (dev->dd.d_dev->dv_type == DEVT_DISK) {
		daddr_t offset;

		offset = dev->d_offset * vd->vdisk_sectorsz;
		offset /= 512;
		blk += offset;
	}
	if (lseek(vd->vdisk_fd, blk << 9, SEEK_SET) == -1)
		return (EIO);

	errno = 0;
	switch (rw & F_MASK) {
	case F_READ:
		rv = read(vd->vdisk_fd, buf, size);
		break;
	case F_WRITE:
		rv = write(vd->vdisk_fd, buf, size);
		break;
	default:
		return (ENOSYS);
	}

	if (errno == 0 && rsize != NULL) {
		*rsize = rv;
	}
	return (errno);
}