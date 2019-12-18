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
typedef  int uint64_t ;
struct TYPE_3__ {size_t d_unit; } ;
struct disk_devdesc {TYPE_1__ dd; } ;
typedef  int daddr_t ;
struct TYPE_4__ {int sectorsize; } ;

/* Variables and functions */
 int CALLBACK (int /*<<< orphan*/ ,size_t,int,char*,size_t,size_t*) ; 
 int EINVAL ; 
 int EROFS ; 
 int F_MASK ; 
 int F_READ ; 
 int F_WRITE ; 
 int /*<<< orphan*/  diskread ; 
 TYPE_2__* ud_info ; 

__attribute__((used)) static int
userdisk_realstrategy(void *devdata, int rw, daddr_t dblk, size_t size,
    char *buf, size_t *rsize)
{
	struct disk_devdesc *dev = devdata;
	uint64_t	off;
	size_t		resid;
	int		rc;

	rw &= F_MASK;
	if (rw == F_WRITE)
		return (EROFS);
	if (rw != F_READ)
		return (EINVAL);
	if (rsize)
		*rsize = 0;
	off = dblk * ud_info[dev->dd.d_unit].sectorsize;
	rc = CALLBACK(diskread, dev->dd.d_unit, off, buf, size, &resid);
	if (rc)
		return (rc);
	if (rsize)
		*rsize = size - resid;
	return (0);
}