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
struct TYPE_3__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_4__ {TYPE_1__ hard; } ;
struct thread_info {TYPE_2__ vfpstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_EN ; 
 int /*<<< orphan*/  NR_CPUS ; 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** vfp_current_hw_state ; 
 scalar_t__ vfp_state_in_hw (unsigned int,struct thread_info*) ; 

__attribute__((used)) static void vfp_force_reload(unsigned int cpu, struct thread_info *thread)
{
	if (vfp_state_in_hw(cpu, thread)) {
		fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
		vfp_current_hw_state[cpu] = NULL;
	}
#ifdef CONFIG_SMP
	thread->vfpstate.hard.cpu = NR_CPUS;
#endif
}