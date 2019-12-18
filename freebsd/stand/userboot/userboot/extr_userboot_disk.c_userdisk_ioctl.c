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
typedef  int /*<<< orphan*/  u_long ;
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_unit; } ;
struct disk_devdesc {TYPE_1__ dd; } ;

/* Variables and functions */
 int CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int ENOTTY ; 
 int disk_ioctl (struct disk_devdesc*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  diskioctl ; 

__attribute__((used)) static int
userdisk_ioctl(struct open_file *f, u_long cmd, void *data)
{
	struct disk_devdesc *dev;
	int rc;

	dev = (struct disk_devdesc *)f->f_devdata;
	rc = disk_ioctl(dev, cmd, data);
	if (rc != ENOTTY)
		return (rc);

	return (CALLBACK(diskioctl, dev->dd.d_unit, cmd, data));
}