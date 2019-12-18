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
 int /*<<< orphan*/  CPUHP_TOPOLOGY_PREPARE ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topology_add_dev ; 
 int /*<<< orphan*/  topology_remove_dev ; 

__attribute__((used)) static int topology_sysfs_init(void)
{
	return cpuhp_setup_state(CPUHP_TOPOLOGY_PREPARE,
				 "base/topology:prepare", topology_add_dev,
				 topology_remove_dev);
}