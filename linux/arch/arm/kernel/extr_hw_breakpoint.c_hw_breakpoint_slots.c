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
#define  TYPE_DATA 129 
#define  TYPE_INST 128 
 int /*<<< orphan*/  debug_arch_supported () ; 
 int get_num_brps () ; 
 int get_num_wrps () ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

int hw_breakpoint_slots(int type)
{
	if (!debug_arch_supported())
		return 0;

	/*
	 * We can be called early, so don't rely on
	 * our static variables being initialised.
	 */
	switch (type) {
	case TYPE_INST:
		return get_num_brps();
	case TYPE_DATA:
		return get_num_wrps();
	default:
		pr_warn("unknown slot type: %d\n", type);
		return 0;
	}
}