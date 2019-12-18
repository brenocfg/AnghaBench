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
struct TYPE_2__ {int fpexc; int /*<<< orphan*/  cpu; int /*<<< orphan*/  fpscr; } ;
union vfp_state {TYPE_1__ hard; } ;
struct thread_info {union vfp_state vfpstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_EN ; 
 int /*<<< orphan*/  FPSCR_ROUND_NEAREST ; 
 int /*<<< orphan*/  NR_CPUS ; 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  memset (union vfp_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 union vfp_state** vfp_current_hw_state ; 

__attribute__((used)) static void vfp_thread_flush(struct thread_info *thread)
{
	union vfp_state *vfp = &thread->vfpstate;
	unsigned int cpu;

	/*
	 * Disable VFP to ensure we initialize it first.  We must ensure
	 * that the modification of vfp_current_hw_state[] and hardware
	 * disable are done for the same CPU and without preemption.
	 *
	 * Do this first to ensure that preemption won't overwrite our
	 * state saving should access to the VFP be enabled at this point.
	 */
	cpu = get_cpu();
	if (vfp_current_hw_state[cpu] == vfp)
		vfp_current_hw_state[cpu] = NULL;
	fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
	put_cpu();

	memset(vfp, 0, sizeof(union vfp_state));

	vfp->hard.fpexc = FPEXC_EN;
	vfp->hard.fpscr = FPSCR_ROUND_NEAREST;
#ifdef CONFIG_SMP
	vfp->hard.cpu = NR_CPUS;
#endif
}