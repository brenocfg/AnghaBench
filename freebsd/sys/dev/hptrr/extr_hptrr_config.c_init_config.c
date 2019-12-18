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
 int /*<<< orphan*/  init_module_him_rr1720 () ; 
 int /*<<< orphan*/  init_module_him_rr174x_rr2210pm () ; 
 int /*<<< orphan*/  init_module_him_rr222x_rr2240 () ; 
 int /*<<< orphan*/  init_module_him_rr2310pm () ; 
 int /*<<< orphan*/  init_module_him_rr232x () ; 
 int /*<<< orphan*/  init_module_him_rr2340 () ; 
 int /*<<< orphan*/  init_module_him_rr2522pm () ; 
 int /*<<< orphan*/  init_module_jbod () ; 
 int /*<<< orphan*/  init_module_partition () ; 
 int /*<<< orphan*/  init_module_raid0 () ; 
 int /*<<< orphan*/  init_module_raid1 () ; 
 int /*<<< orphan*/  init_module_raid5 () ; 
 int /*<<< orphan*/  init_module_vdev_raw () ; 

int init_config(void)
{
	init_module_him_rr2310pm();
	init_module_him_rr174x_rr2210pm();
	init_module_him_rr2522pm();
	init_module_him_rr2340();
	init_module_him_rr222x_rr2240();
	init_module_him_rr1720();
	init_module_him_rr232x();
	init_module_vdev_raw();
	init_module_partition();
	init_module_raid0();
	init_module_raid1();
	init_module_raid5();
	init_module_jbod();
	return 0;
}