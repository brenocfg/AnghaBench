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
struct fpu {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct fpu fpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  fpstate_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_x86_fpu_init_state (struct fpu*) ; 

__attribute__((used)) static void fpu__initialize(struct fpu *fpu)
{
	WARN_ON_FPU(fpu != &current->thread.fpu);

	set_thread_flag(TIF_NEED_FPU_LOAD);
	fpstate_init(&fpu->state);
	trace_x86_fpu_init_state(fpu);
}