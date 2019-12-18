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
 int ENOMEM ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/ * fuse_dev ; 
 int /*<<< orphan*/  fuse_device_cdevsw ; 
 int /*<<< orphan*/ * make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
fuse_device_init(void)
{

	fuse_dev = make_dev(&fuse_device_cdevsw, 0, UID_ROOT, GID_OPERATOR,
	    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, "fuse");
	if (fuse_dev == NULL)
		return (ENOMEM);
	return (0);
}