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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  cd_info; } ;

/* Variables and functions */
 int cdrom_ioctl (int /*<<< orphan*/ ,struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 TYPE_1__ gd ; 
 int /*<<< orphan*/  gdrom_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gdrom_bdops_ioctl(struct block_device *bdev, fmode_t mode,
	unsigned cmd, unsigned long arg)
{
	int ret;

	mutex_lock(&gdrom_mutex);
	ret = cdrom_ioctl(gd.cd_info, bdev, mode, cmd, arg);
	mutex_unlock(&gdrom_mutex);

	return ret;
}