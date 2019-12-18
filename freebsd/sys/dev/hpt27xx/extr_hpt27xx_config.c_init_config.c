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
 int /*<<< orphan*/  init_module_him_rr2720 () ; 
 int /*<<< orphan*/  init_module_him_rr273x () ; 
 int /*<<< orphan*/  init_module_him_rr276x () ; 
 int /*<<< orphan*/  init_module_him_rr278x () ; 
 int /*<<< orphan*/  init_module_jbod () ; 
 int /*<<< orphan*/  init_module_partition () ; 
 int /*<<< orphan*/  init_module_raid0 () ; 
 int /*<<< orphan*/  init_module_raid1 () ; 
 int /*<<< orphan*/  init_module_raid5 () ; 
 int /*<<< orphan*/  init_module_vdev_raw () ; 

int init_config(void)
{
	init_module_him_rr2720();
	init_module_him_rr273x();
	init_module_him_rr276x();
	init_module_him_rr278x();
	init_module_vdev_raw();
	init_module_partition();
	init_module_raid0();
	init_module_raid1();
	init_module_raid5();
	init_module_jbod();
	return 0;
}