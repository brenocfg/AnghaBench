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
struct sh_fpu_soft_struct {int dummy; } ;
struct sh_fpu_hard_struct {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CPU_HAS_FPU ; 
 scalar_t__ HAVE_SOFTFP ; 
 TYPE_1__ boot_cpu_data ; 
 int xstate_size ; 

void init_thread_xstate(void)
{
	if (boot_cpu_data.flags & CPU_HAS_FPU)
		xstate_size = sizeof(struct sh_fpu_hard_struct);
	else if (HAVE_SOFTFP)
		xstate_size = sizeof(struct sh_fpu_soft_struct);
	else
		xstate_size = 0;
}