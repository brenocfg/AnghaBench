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
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fuse_dev ; 

void
fuse_device_destroy(void)
{

	MPASS(fuse_dev != NULL);
	destroy_dev(fuse_dev);
}