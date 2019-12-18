#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CPU_HAS_FPU ; 
 int /*<<< orphan*/  clear_used_math () ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  disable_fpu () ; 
 scalar_t__ fpu_disabled ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void fpu_init(void)
{
	/* Disable the FPU */
	if (fpu_disabled && (current_cpu_data.flags & CPU_HAS_FPU)) {
		printk("FPU Disabled\n");
		current_cpu_data.flags &= ~CPU_HAS_FPU;
	}

	disable_fpu();
	clear_used_math();
}