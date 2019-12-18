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
typedef  int /*<<< orphan*/  uint32_t ;
struct disk_devdesc {int dummy; } ;
typedef  size_t lbasize_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__ SI (struct disk_devdesc*) ; 
 int /*<<< orphan*/  debugf (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stor_printf (char*,...) ; 
 int ub_dev_read (int /*<<< orphan*/ ,char*,size_t,scalar_t__,size_t*) ; 

__attribute__((used)) static int
stor_readdev(struct disk_devdesc *dev, daddr_t blk, size_t size, char *buf)
{
	lbasize_t real_size;
	int err;

	debugf("reading blk=%d size=%d @ 0x%08x\n", (int)blk, size, (uint32_t)buf);

	err = ub_dev_read(SI(dev).handle, buf, size, blk, &real_size);
	if (err != 0) {
		stor_printf("read failed, error=%d\n", err);
		return (EIO);
	}

	if (real_size != size) {
		stor_printf("real size != size\n");
		err = EIO;
	}

	return (err);
}