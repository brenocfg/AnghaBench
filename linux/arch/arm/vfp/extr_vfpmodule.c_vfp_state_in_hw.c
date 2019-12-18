#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int cpu; } ;
struct TYPE_4__ {TYPE_1__ hard; } ;
struct thread_info {TYPE_2__ vfpstate; } ;

/* Variables and functions */
 TYPE_2__** vfp_current_hw_state ; 

__attribute__((used)) static bool vfp_state_in_hw(unsigned int cpu, struct thread_info *thread)
{
#ifdef CONFIG_SMP
	if (thread->vfpstate.hard.cpu != cpu)
		return false;
#endif
	return vfp_current_hw_state[cpu] == &thread->vfpstate;
}