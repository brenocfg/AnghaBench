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
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_susp_dev ; 
 int /*<<< orphan*/  ffs_susp_lock ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void
ffs_susp_uninitialize(void)
{

	destroy_dev(ffs_susp_dev);
	sx_destroy(&ffs_susp_lock);
}