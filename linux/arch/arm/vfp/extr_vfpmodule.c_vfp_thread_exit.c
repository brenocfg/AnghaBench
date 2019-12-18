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
typedef  union vfp_state {int dummy; } vfp_state ;
struct thread_info {union vfp_state vfpstate; } ;

/* Variables and functions */
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 union vfp_state** vfp_current_hw_state ; 

__attribute__((used)) static void vfp_thread_exit(struct thread_info *thread)
{
	/* release case: Per-thread VFP cleanup. */
	union vfp_state *vfp = &thread->vfpstate;
	unsigned int cpu = get_cpu();

	if (vfp_current_hw_state[cpu] == vfp)
		vfp_current_hw_state[cpu] = NULL;
	put_cpu();
}