#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fpsr; } ;
struct TYPE_5__ {TYPE_3__ fpsimd_state; } ;
struct TYPE_6__ {TYPE_1__ uw; int /*<<< orphan*/  sve_vl; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  fpsimd_load_state (TYPE_3__*) ; 
 int /*<<< orphan*/  have_cpu_fpsimd_context () ; 
 int /*<<< orphan*/  sve_load_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sve_pffr (TYPE_2__*) ; 
 scalar_t__ sve_vq_from_vl (int /*<<< orphan*/ ) ; 
 scalar_t__ system_supports_sve () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_fpsimd_load(void)
{
	WARN_ON(!have_cpu_fpsimd_context());

	if (system_supports_sve() && test_thread_flag(TIF_SVE))
		sve_load_state(sve_pffr(&current->thread),
			       &current->thread.uw.fpsimd_state.fpsr,
			       sve_vq_from_vl(current->thread.sve_vl) - 1);
	else
		fpsimd_load_state(&current->thread.uw.fpsimd_state);
}