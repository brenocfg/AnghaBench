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
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  membar_safe (char*) ; 
 scalar_t__ penguins_are_doing_time ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_capture_depth ; 
 int /*<<< orphan*/  smp_capture_registry ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void smp_release(void)
{
	if (atomic_dec_and_test(&smp_capture_depth)) {
#ifdef CAPTURE_DEBUG
		printk("CPU[%d]: Giving pardon to "
		       "imprisoned penguins\n",
		       smp_processor_id());
#endif
		penguins_are_doing_time = 0;
		membar_safe("#StoreLoad");
		atomic_dec(&smp_capture_registry);
	}
}