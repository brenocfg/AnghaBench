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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int const u_long ;
struct open_file {scalar_t__ f_devdata; } ;
struct disk_devdesc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int EINVAL ; 
 int ENOTTY ; 
 int ENXIO ; 
 int disk_ioctl (struct disk_devdesc*,int const,void*) ; 
 TYPE_1__ umass_uaa ; 
 int /*<<< orphan*/  usb_msc_read_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
umass_disk_ioctl(struct open_file *f, u_long cmd, void *buf)
{
	struct disk_devdesc *dev;
	uint32_t nblock;
	uint32_t blocksize;
	int rc;

	dev = (struct disk_devdesc *)(f->f_devdata);
	if (dev == NULL)
		return (EINVAL);

	rc = disk_ioctl(dev, cmd, buf);
	if (rc != ENOTTY)
		return (rc);

	switch (cmd) {
	case DIOCGSECTORSIZE:
	case DIOCGMEDIASIZE:
		if (usb_msc_read_capacity(umass_uaa.device, 0,
		    &nblock, &blocksize) != 0)
			return (EINVAL);

		if (cmd == DIOCGMEDIASIZE)
			*(uint64_t*)buf = nblock;
		else
			*(uint32_t*)buf = blocksize;

		return (0);
	default:
		return (ENXIO);
	}
}