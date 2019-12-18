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
typedef  int u32 ;
struct thread_info {int /*<<< orphan*/  vfpstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_EN ; 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  vfp_save_state (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vfp_state_in_hw (unsigned int,struct thread_info*) ; 

void vfp_sync_hwstate(struct thread_info *thread)
{
	unsigned int cpu = get_cpu();

	if (vfp_state_in_hw(cpu, thread)) {
		u32 fpexc = fmrx(FPEXC);

		/*
		 * Save the last VFP state on this CPU.
		 */
		fmxr(FPEXC, fpexc | FPEXC_EN);
		vfp_save_state(&thread->vfpstate, fpexc | FPEXC_EN);
		fmxr(FPEXC, fpexc);
	}

	put_cpu();
}