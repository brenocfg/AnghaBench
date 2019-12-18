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
struct disk_devdesc {size_t d_offset; } ;
typedef  size_t daddr_t ;
struct TYPE_2__ {size_t bsize; } ;

/* Variables and functions */
 int EIO ; 
 int EROFS ; 
 int F_MASK ; 
 int F_READ ; 
 TYPE_1__ SI (struct disk_devdesc*) ; 
 int /*<<< orphan*/  stor_printf (char*,...) ; 
 int stor_readdev (struct disk_devdesc*,size_t,size_t,char*) ; 

__attribute__((used)) static int
stor_strategy(void *devdata, int rw, daddr_t blk, size_t size,
    char *buf, size_t *rsize)
{
	struct disk_devdesc *dev = (struct disk_devdesc *)devdata;
	daddr_t bcount;
	int err;

	rw &= F_MASK;
	if (rw != F_READ) {
		stor_printf("write attempt, operation not supported!\n");
		return (EROFS);
	}

	if (size % SI(dev).bsize) {
		stor_printf("size=%zu not multiple of device "
		    "block size=%d\n",
		    size, SI(dev).bsize);
		return (EIO);
	}
	bcount = size / SI(dev).bsize;
	if (rsize)
		*rsize = 0;

	err = stor_readdev(dev, blk + dev->d_offset, bcount, buf);
	if (!err && rsize)
		*rsize = size;

	return (err);
}