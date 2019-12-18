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
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_ncpus ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  taskq_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_file_taskq ; 

void
vdev_file_init(void)
{
	vdev_file_taskq = taskq_create("z_vdev_file", MAX(max_ncpus, 16),
	    minclsyspri, max_ncpus, INT_MAX, 0);
}