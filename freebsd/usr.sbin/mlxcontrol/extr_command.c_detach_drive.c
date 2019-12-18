#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  MLX_DETACH_DRIVE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctrlrpath (int) ; 
 int /*<<< orphan*/  drivename (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
detach_drive(int unit, void *arg)
{
    int		fd;
    
    /* Get the device */
    if ((fd = open(ctrlrpath(unit), 0)) < 0) {
	warn("can't open %s", ctrlrpath(unit));
	return;
    }

    if (ioctl(fd, MLX_DETACH_DRIVE, &unit) < 0)
	warn("can't detach %s", drivename(unit));
    close(fd);
}